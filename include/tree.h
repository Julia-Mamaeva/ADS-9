// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class JKL_Tree {
 public:
    JKL_Tree(const std::vector<char>& xyz_elem);
    
    struct MNO_Node {
        char x_val;
        std::vector<std::shared_ptr<MNO_Node>> x_children;
        
        MNO_Node(char y_val) : x_val(y_val) {}
    };
    
    std::shared_ptr<MNO_Node> gRoot() const { return p_root; }
    size_t gPermCount() const { return t_perm; }

 private:
    std::shared_ptr<MNO_Node> p_root;
    size_t t_perm;
    
    void bTree(std::shared_ptr<MNO_Node> prnt, 
              const std::vector<char>& remElem);
};

std::vector<std::vector<char>> gAllPerm(const JKL_Tree& tr);
std::vector<char> gPermFrst(const JKL_Tree& tr, int nm);
std::vector<char> gPermScnd(const JKL_Tree& tr, int nm);

#endif  // INCLUDE_TREE_H_
