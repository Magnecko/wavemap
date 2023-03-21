#ifndef WAVEMAP_DATA_STRUCTURE_CHUNKED_NDTREE_CHUNKED_NDTREE_H_
#define WAVEMAP_DATA_STRUCTURE_CHUNKED_NDTREE_CHUNKED_NDTREE_H_

#include <string>
#include <utility>
#include <vector>

#include "wavemap/common.h"
#include "wavemap/data_structure/chunked_ndtree/chunked_ndtree_node.h"
#include "wavemap/indexing/ndtree_index.h"
#include "wavemap/iterator/subtree_iterator.h"

namespace wavemap {
template <typename NodeDataT, int dim, int chunk_height>
class ChunkedNdtree {
 public:
  using IndexType = NdtreeIndex<dim>;
  using NodeType = ChunkedNdtreeNode<NodeDataT, dim, chunk_height>;
  using NodeDataType = NodeDataT;
  static constexpr int kChunkHeight = chunk_height;

  explicit ChunkedNdtree(int max_height);
  ~ChunkedNdtree() = default;

  bool empty() const { return root_node_.empty(); }
  size_t size() const;
  void clear() { root_node_.clear(); }
  void prune();

  bool hasNode(const IndexType& index) const;
  void allocateNode(const IndexType& index);
  void resetNode(const IndexType& index);
  NodeDataT* getNodeData(const IndexType& index, bool auto_allocate = true);
  const NodeDataT* getNodeData(const IndexType& index) const;

  int getMaxHeight() const { return max_height_; }
  NodeType& getRootNode() { return root_node_; }
  const NodeType& getRootNode() const { return root_node_; }

  template <TraversalOrder traversal_order>
  auto getIterator() {
    return Subtree<NodeType, traversal_order>(&root_node_);
  }
  template <TraversalOrder traversal_order>
  auto getIterator() const {
    return Subtree<const NodeType, traversal_order>(&root_node_);
  }

  size_t getMemoryUsage() const;

 private:
  NodeType root_node_;
  const int max_height_;

  std::pair<NodeType*, LinearIndex> getNodeAndRelativeIndex(
      const IndexType& index, bool auto_allocate);
  std::pair<const NodeType*, LinearIndex> getNodeAndRelativeIndex(
      const IndexType& index) const;
};
}  // namespace wavemap

#include "wavemap/data_structure/chunked_ndtree/impl/chunked_ndtree_inl.h"

#endif  // WAVEMAP_DATA_STRUCTURE_CHUNKED_NDTREE_CHUNKED_NDTREE_H_
