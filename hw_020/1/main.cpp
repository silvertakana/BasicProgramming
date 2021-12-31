#include <iostream>
struct Tnode
{
   int key;
   Tnode* left = nullptr;
   Tnode* right = nullptr;
   int evenLeaf() const
   {
      int total = (key % 2 == 0) ? 1 : 0;
      if (left)total += left->evenLeaf();
      if (right)total += right->evenLeaf();
      return total;
   }
   int countNodes(const int& k) const
   {
      int total = (key > k) ? 1 : 0;
      if (left)total += left->countNodes(k);
      if (right)total += right->countNodes(k);
      return total;
   }
   int oddSum() const 
   {
      int total = (key % 2 != 0) ? 1 : 0;
      if (left)total += left->oddSum();
      if (right)total += right->oddSum();
      return total;
   }
   int evenMax() const 
   {
      int max = (key % 2 == 0) ? key : INT_MIN;
      if (left)
      {
         int leftMax = left->evenMax();
         if (leftMax > max)
            max = leftMax;
      }
      if (right)
      {
         int rightMax = right->evenMax();
         if (rightMax > max)
            max = rightMax;
      }
      return max;
   }
   bool isLeft(const int& k) const 
   {
      bool isSmaller = key < k;
      if (left && !left->isLeft(k)) isSmaller = false;
      if (right && !right->isLeft(k)) isSmaller = false;
      return isSmaller;
   }
   size_t depth() const 
   {
      int d = 1;
      if (left)
      {
         int leftDepth = left->depth()+1;
         if (leftDepth > d)
            d = leftDepth;
      }
      if (right)
      {
         int rightDepth = right->depth() + 1;
         if (rightDepth > d)
            d = rightDepth;
      }
      return d;
   }
   bool isBST()const
   {
      if (!left && right || !right && left) return false;
      else return abs((long)(left->depth() - right->depth())) <= 1;
   }
   ~Tnode()
   {
      delete left;
      delete right;
   }
};
int main()
{
   {
      Tnode* root = new Tnode{ 2 };
      {
         root->left = new Tnode{ 7 };
         {
            root->left->left = new Tnode{ 2 };
            root->left->right = new Tnode{ 6 };
            {
               root->left->right->left = new Tnode{ 5 };
               root->left->right->right = new Tnode{ 11 };
            }
         }
         root->right = new Tnode{ 5 };
         {
            root->right->right = new Tnode{ 9 };
            {
               root->right->right->left = new Tnode{ 4 };
            }
         }
      }


      std::cout << root->evenLeaf() << std::endl;
      std::cout << root->countNodes(2) << std::endl;
      std::cout << root->oddSum() << std::endl;
      std::cout << root->evenMax() << std::endl;
      std::cout << std::boolalpha << root->isLeft(12) << std::endl;
      std::cout << root->depth() << std::endl;
      std::cout << root->isBST() << std::endl;

      delete root;
   }
   {
      Tnode* root2 = new Tnode{ 1 };
      {
      root2->left = new Tnode{ 2 };
      {
         root2->left->left = new Tnode{ 4 };
         root2->left->right = new Tnode{ 5 };
         {
            root2->left->right->left = new Tnode{ 6 };
         }
      }
      //root2->right = new Tnode{ 3 };
      }
      std::cout << root2->depth() << std::endl;
      std::cout << root2->isBST() << std::endl;
      delete root2;
   }
}