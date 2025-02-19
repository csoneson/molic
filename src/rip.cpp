#include "rip.h"
// #include "set_ops.h"  // For set_any
// #include <unordered_map>

// using VS = std::vector<std::string>;

//' Maximum Cardinality Search
//' 
//' @param adj A named adjacency list of a decomposable grah
//' @details If adj is not the adjacency list of a decomposable graph an error is raised
//' @return A list with a perfect numbering of the nodes and a perfect sequence of sets
//' @examples
//' x <- list(a = c("b", "d"), b = c("a", "c", "d"), c = c("b", "d"), d = c("a", "c", "b"))
//' mcs(x)
//' @export
// [[Rcpp::export]]
Rcpp::List mcs(Rcpp::List & adj) {
  VS  nodes = adj.names();
  int N = nodes.size();
  // Raise a WARNING if adj is the empty graph
  // if( !( N - 1 )) return VS(nodes[0]);
  std::unordered_map<std::string, int> labels; // = {};
  for( int i = 0; i < N; i++ ) {
    labels.emplace(nodes[i], 0);
  }
  VVS ps(N);
  decltype(nodes) remaining_nodes = nodes;
  decltype(nodes) used_nodes(N, "");
  auto v = nodes[0];
  used_nodes[0] = v;
  ps[0] = {v};
  remaining_nodes.erase(remaining_nodes.begin()+0);
  for( int i = 1; i < N; i++ ) {
    auto ne_i = Rcpp::as<VS>(adj[v]);
    // Increment neighbor nodes with a one
    for (auto it = ne_i.begin(); it != ne_i.end(); ++it) {
      auto ne_ = labels.find(*it);
      ne_->second++;
    }
    std::string max_v;
    int max_val = -1;
    VS::iterator max_it;
    for (auto it = remaining_nodes.begin(); it != remaining_nodes.end(); ++it) {
      auto rn = labels.find(*it);
      int max_candidate = rn->second;
      if( max_candidate > max_val ) {
	max_v   = *it;
	max_val = max_candidate;
	max_it  = it;
      }
    }
    v = max_v;
    used_nodes[i] = v;
    remaining_nodes.erase(max_it);
    auto ne_v = Rcpp::as<VS>(adj[v]);
    ne_v.push_back(v); // The closure of v
    VS anc    = VS(used_nodes.begin(), used_nodes.begin() + i + 1);
    VS B_i     = set_intersect(ne_v, anc);
    int card_i = B_i.size();
    if ( i > 1 && card_i > 2) {
      // ----------------------------------------------------------------------------------------------
      // Test for decomposability for step i. See Lauritzen for details
      // 1. cl(v_i) \cap {v_1, .., v_{i-1}} needs to be complete
      // 2. The check is always positive for i \in {1,2}
      // 3. It is not neccesarry to check for ||ne_v|| < 3 since these are always complete in the graph
      // ----------------------------------------------------------------------------------------------
      for (int j = 0; j < card_i; j++) {
    	for (int k = j + 1; k < card_i - 1; k++) {
	  auto adj_k = Rcpp::as<VS>(adj[B_i[k]]);
    	  if ( !set_in(B_i[j], adj_k) ) Rcpp::stop("The corresponding graph of <adj> is not decomposable");
    	}
      }
    }
    ps[i] = B_i;
  }
  return Rcpp::List::create(Rcpp::_["po"] = used_nodes , Rcpp::_["ps"] = ps);
} 

// [[Rcpp::export]]
VVS perfect_cliques(VVS & x) {
  // In: 
  // x: a perfect sequence of sets (denoted B_i in Lauritzen)
  //
  // Out:
  // y: a perfect sequence of the cliques
  int n = x.size();
  VVS pc;
  for(int i = 0; i < n; i++) {
    std::vector<bool> v; // Dummy var to loop over
    for(int j = 0; j < n; j++) {
      if( j != i ) {
	v.push_back(set_issubeq(x[i], x[j]));
      }
    }
    if( !set_any(v) ) {
      pc.push_back(x[i]); 
    }
  }
  return pc;
}

// [[Rcpp::export]]
Rcpp::List perfect_separators(VVS & x) {
  // x: Cliques (with RIP ordering)
  // S_j := H_{j-1} \cap C_j, H_{j-1} := \cap_k C_{k-1}, k = 1, 2, ..., j-1
  int n = x.size();
  Rcpp::List ps(n);       // All elements initialized to NULL
  if( n == 1 ) return ps; // List::create(_[""] = R_NilValue);
  for (int i = 1; i < n; i++) {
    VS Hi_1;
    for (int j = 0; j < i; j++) {
      Hi_1.insert(Hi_1.end(), x[j].begin(), x[j].end());
    }
    ps[i] = set_intersect(x[i], Hi_1);
  }
  return ps;
}

//' Runnining Intersection Property
//' @description Given a decomposable graph, this functions finds a perfect numbering on the vertices using maximum cardinality search, and hereafter returns a list with two elements: "C" - A RIP-ordering of the cliques and "S" - A RIP ordering of the separators.
//'
//' @param adj A named adjacency list of a decomposable graph
//' @seealso \code{\link{mcs}}, \code{\link{is_decomposable}} 
//' @examples
//' x <- list(a = c("b", "d"), b = c("a", "c", "d"), c = c("b", "d"), d = c("a", "c", "b"))
//' y <- rip(x)
//' # Cliques:
//' y$C
//' # Separators:
//' y$S
//' @export
// [[Rcpp::export]]
Rcpp::List rip(Rcpp::List & adj) {
  auto  z = mcs(adj);
  VVS pseq = z["ps"];
  VVS pc   = perfect_cliques(pseq);
  Rcpp::List ps = perfect_separators(pc);
  return Rcpp::List::create(Rcpp::_["C"] = pc , Rcpp::_["S"] = ps);
}


// -------------------------------------------------------------------------
// Used in backward selection where we dont need to test for decomposability
// -------------------------------------------------------------------------
// [[Rcpp::export]]
Rcpp::List mcs2(Rcpp::List & adj) {
  VS  nodes = adj.names();
  int N = nodes.size();
  // Raise a WARNING if adj is the empty graph
  // if( !( N - 1 )) return VS(nodes[0]);
  std::unordered_map<std::string, int> labels; // = {};
  for( int i = 0; i < N; i++ ) {
    labels.emplace(nodes[i], 0);
  }
  VVS ps(N);
  decltype(nodes) remaining_nodes = nodes;
  decltype(nodes) used_nodes(N, "");
  auto v = nodes[0];
  used_nodes[0] = v;
  ps[0] = {v};
  remaining_nodes.erase(remaining_nodes.begin()+0);
  for( int i = 1; i < N; i++ ) {
    auto ne_i = Rcpp::as<VS>(adj[v]);
    // Increment neighbor nodes with a one
    for (auto it = ne_i.begin(); it != ne_i.end(); ++it) {
      auto ne_ = labels.find(*it);
      ne_->second++;
    }
    std::string max_v;
    int max_val = -1;
    VS::iterator max_it;
    for (auto it = remaining_nodes.begin(); it != remaining_nodes.end(); ++it) {
      auto rn = labels.find(*it);
      int max_candidate = rn->second;
      if( max_candidate > max_val ) {
	max_v   = *it;
	max_val = max_candidate;
	max_it  = it;
      }
    }
    v = max_v;
    used_nodes[i] = v;
    remaining_nodes.erase(max_it);
    auto ne_v = Rcpp::as<VS>(adj[v]);
    ne_v.push_back(v); // The closure of v
    VS anc    = VS(used_nodes.begin(), used_nodes.begin() + i + 1);
    VS B_i     = set_intersect(ne_v, anc);
    ps[i] = B_i;
  }
  return Rcpp::List::create(Rcpp::_["po"] = used_nodes , Rcpp::_["ps"] = ps);
}

// [[Rcpp::export]]
Rcpp::List rip2(Rcpp::List & adj) {
  auto  z = mcs2(adj);
  VVS pseq = z["ps"];
  VVS pc   = perfect_cliques(pseq);
  Rcpp::List ps = perfect_separators(pc);
  return Rcpp::List::create(Rcpp::_["C"] = pc , Rcpp::_["S"] = ps);
}
