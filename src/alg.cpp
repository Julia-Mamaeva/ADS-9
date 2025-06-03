// Copyright 2022 NNTU-CS
#include <vector>
#include <memory>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root_ = nullptr;
        total_permutations_ = 0;
        return;
    }

    root_ = std::make_shared<Node>('\0');
    total_permutations_ = 1;

    for (size_t i = 1; i <= elements.size(); ++i) {
        total_permutations_ *= i;
    }

    buildTree(root_, elements);
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
                      const std::vector<char>& remaining_elements) {
    if (remaining_elements.empty()) {
        return;
    }

    for (char elem : remaining_elements) {
        auto child = std::make_shared<Node>(elem);
        parent->children.push_back(child);

        std::vector<char> new_remaining;
        for (char e : remaining_elements) {
            if (e != elem) {
                new_remaining.push_back(e);
            }
        }

        buildTree(child, new_remaining);
    }
}

void collectPermutations(std::shared_ptr<PMTree::Node> node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.getRoot()) {
        return result;
    }

    std::vector<char> current;
    collectPermutations(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto all_perms = getAllPerms(tree);
    if (num <= 0 || static_cast<size_t>(num) > all_perms.size()) {
        return {};
    }
    return all_perms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num <= 0 || static_cast<size_t>(num) > tree.getPermutationsCount()) {
        return {};
    }

    std::vector<char> result;
    auto current = tree.getRoot();
    num--;

    std::vector<int> indices;
    size_t n = current->children.size();
    size_t divisor = 1;

    for (size_t i = 1; i <= n; ++i) {
        divisor *= i;
    }

    size_t remaining = num;
    for (size_t i = n; i >= 1; --i) {
        divisor /= i;
        size_t index = remaining / divisor;
        indices.push_back(index);
        remaining %= divisor;
    }

    current = tree.getRoot();
    for (int index : indices) {
        if (index < 0 || static_cast<size_t>(index) >=
            current->children.size()) {
            return {};
        }
        current = current->children[index];
        result.push_back(current->value);
    }

    return result;
}
