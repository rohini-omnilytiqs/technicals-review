class TreeNode:
    def __init__(self, value, left, right):
        self.value = value
        self.left = left
        self.right = right
    
    # in order is left->curr->right
    @classmethod
    def in_order_traversal(self, root, traversal):
        if root.left is not None:
            self.in_order_traversal(root.left, traversal)
        traversal.append(root.value)
        if root.right is not None:
            self.in_order_traversal(root.right, traversal)

    # post order is left->right->root
    @classmethod
    def post_order_traversal(self, root, traversal):
        if root.left is not None:
            self.post_order_traversal(root.left, traversal)
        if root.right is not None:
            self.post_order_traversal(root.right, traversal)
        traversal.append(root.value)
    
    # pre order is root->left->right
    @classmethod
    def pre_order_traversal(self, root, traversal):
        if root is not None:
            traversal.append(root.value)
        if root.left is not None:
            self.pre_order_traversal(root.left, traversal)
        if root.right is not None:
            self.pre_order_traversal(root.right, traversal)

leaf1 = TreeNode(4, None, None)
leaf2 = TreeNode(5, None, None)
leaf3 = TreeNode(1, None, None)
leaf4 = TreeNode(9, None, None)

mid1 = TreeNode(12, leaf1, leaf2)
mid2 = TreeNode(0, leaf3, leaf4)
root = TreeNode(100, mid1, mid2)

in_order_traversal = []
TreeNode.in_order_traversal(root, in_order_traversal)
print(in_order_traversal)

post_order_traversal = []
TreeNode.post_order_traversal(root, post_order_traversal)
print(post_order_traversal)

pre_order_traversal = []
TreeNode.pre_order_traversal(root, pre_order_traversal)
print(pre_order_traversal)

