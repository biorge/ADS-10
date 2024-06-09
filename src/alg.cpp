// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
Tree::Tree(const std::string& elements) : elements(elements) {
  root = new Node('\0');  // Корень дерева не содержит значения
  buildTree(root, elements);
}

Tree::~Tree() { destroyTree(root); }

void Tree::buildTree(Node* node, const std::string& remaining_elements) {
  if (remaining_elements.empty()) return;
  for (char ch : remaining_elements) {
    Node* child = new Node(ch);
    node->children.push_back(child);
    std::string next_remaining = remaining_elements;
    next_remaining.erase(next_remaining.find(ch), 1);
    buildTree(child, next_remaining);
  }
}

void Tree::destroyTree(Node* node) {
  if (node) {
    for (Node* child : node->children) {
      destroyTree(child);
    }
    delete node;
  }
}

std::vector<std::vector<char>> Tree::generatePermutations() const {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  generatePermutations(root, current, result);
  return result;
}

void Tree::generatePermutations(Node* node, std::vector<char>& current,
                                std::vector<std::vector<char>>& result) const {
  if (!node->children.empty()) {
    for (Node* child : node->children) {
      current.push_back(child->value);
      generatePermutations(child, current, result);
      current.pop_back();
    }
  } else {
    result.push_back(current);
  }
}

std::vector<char> getPerm(const Tree& tree, int n) {
  auto permutations = tree.generatePermutations();
  if (n < 0 || n >= permutations.size()) {
    throw std::out_of_range("Index out of range");
  }
  return permutations[n];
}
