// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"

JKL_Tree::JKL_Tree(const std::vector<char>& xyz_elem) {
    if (xyz_elem.empty()) {
        p_root = nullptr;
        t_perm = 0;
        return;
    } 
    
    p_root = std::make_shared<MNO_Node>('\0');
    t_perm = 1;
    
    for (size_t i = 1; i <= xyz_elem.size(); ++i) {
        t_perm *= i;
    }
    
    bTree(p_root, xyz_elem);
}

void JKL_Tree::bTree(std::shared_ptr<MNO_Node> prnt,
                    const std::vector<char>& remElem) {
    if (remElem.empty()) {
        return;
    }
    
    for (char el : remElem) {
        auto chld = std::make_shared<MNO_Node>(el);
        prnt->x_children.push_back(chld);
        
        std::vector<char> newRem;
        for (char e : remElem) {
            if (e != el) {
                newRem.push_back(e);
            }
        }
        
        bTree(chld, newRem);
    }
}

void cPerm(std::shared_ptr<JKL_Tree::MNO_Node> nd, 
          std::vector<char>& curr, 
          std::vector<std::vector<char>>& res) {
    if (nd->x_val != '\0') {
        curr.push_back(nd->x_val);
    }
    
    if (nd->x_children.empty()) {
        res.push_back(curr);
    } else {
        for (const auto& ch : nd->x_children) {
            cPerm(ch, curr, res);
        }
    }
    
    if (nd->x_val != '\0') {
        curr.pop_back();
    }
}

std::vector<std::vector<char>> gAllPerm(const JKL_Tree& tr) {
    std::vector<std::vector<char>> res;
    if (!tr.gRoot()) {
        return res;
    }
    
    std::vector<char> curr;
    cPerm(tr.gRoot(), curr, res);
    return res;
}

std::vector<char> gPermFrst(const JKL_Tree& tr, int nm) {
    auto allP = gAllPerm(tr);
    if (nm <= 0 || static_cast<size_t>(nm) > allP.size()) {
        return {};
    }
    return allP[nm - 1];
}

std::vector<char> gPermScnd(const JKL_Tree& tr, int nm) {
    if (nm <= 0 || static_cast<size_t>(nm) > tr.gPermCount()) {
        return {};
    }
    
    std::vector<char> res;
    auto curr = tr.gRoot();
    nm--;
    
    std::vector<int> idx;
    size_t n = curr->x_children.size();
    size_t div = 1;
    
    for (size_t i = 1; i <= n; ++i) {
        div *= i;
    }
    
    size_t rem = nm;
    for (size_t i = n; i >= 1; --i) {
        div /= i;
        size_t id = rem / div;
        idx.push_back(id);
        rem %= div;
    }
    
    curr = tr.gRoot();
    for (int id : idx) {
        if (id < 0 || static_cast<size_t>(id) >= curr->x_children.size()) {
            return {};
        }
        curr = curr->x_children[id];
        res.push_back(curr->x_val);
    }
    
    return res;
}
