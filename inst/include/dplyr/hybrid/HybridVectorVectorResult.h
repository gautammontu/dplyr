#ifndef DPLYR_HYBRID_HybridVectorVectorResult_H
#define DPLYR_HYBRID_HybridVectorVectorResult_H

namespace dplyr {
namespace hybrid {

template <int RTYPE, typename Data, typename Impl>
class HybridVectorVectorResult {
public:
  typedef typename Rcpp::Vector<RTYPE> Vec ;
  typedef typename Data::group_iterator group_iterator ;
  typedef typename Data::slicing_index Index;
  typedef typename Vec::stored_type stored_type;

  HybridVectorVectorResult(const Data& data_) :
    data(data_)
  {}

  inline Vec window() const {
    int ng = data.ngroups();
    int nr = data.nrows();

    Vec vec = init(nr);

    group_iterator git = data.group_begin();
    for (int i = 0; i < ng; i++, ++git) {
      self()->fill(*git, vec);
    }

    return vec ;
  }

  inline SEXP summarise() const {
    // we let R handle it
    return R_UnboundValue;
  }

private:
  const Data& data;

  inline const Impl* self() const {
    return static_cast<const Impl*>(this);
  }

  inline Vec init(int n) const {
    return Rcpp::no_init(n);
  }

};

}
}



#endif
