#ifndef NODE_TREE_SITTER_TREE_H_
#define NODE_TREE_SITTER_TREE_H_

#include "tree_sitter/api.h"

#include <nan.h>
#include <node_object_wrap.h>
#include <unordered_map>
#include <v8.h>

namespace node_tree_sitter {

class Tree final : public Nan::ObjectWrap {
 public:
  Tree(const Tree &);
  Tree(Tree &&) noexcept;
  Tree &operator=(const Tree &);
  Tree &operator=(Tree &&) noexcept;
  static void Init(v8::Local<v8::Object> exports);
  static v8::Local<v8::Value> NewInstance(TSTree *);
  static const Tree *UnwrapTree(const v8::Local<v8::Value> &);

  struct NodeCacheEntry {
    Tree *tree;
    const void *key;
    v8::Persistent<v8::Object> node;
  };

  TSTree *tree_;
  std::unordered_map<const void *, NodeCacheEntry *> cached_nodes_;

 private:
  explicit Tree(TSTree *);
  ~Tree() final;

  static void New(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void Edit(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void RootNode(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void PrintDotGraph(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void GetEditedRange(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void GetChangedRanges(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void CacheNode(const Nan::FunctionCallbackInfo<v8::Value> &);
  static void CacheNodes(const Nan::FunctionCallbackInfo<v8::Value> &);

  static Nan::Persistent<v8::Function> constructor;
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
};

}  // namespace node_tree_sitter

#endif  // NODE_TREE_SITTER_TREE_H_
