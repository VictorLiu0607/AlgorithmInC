class TreeNode:
    """
    节点
    """

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def levelOrderBottom(self, root):
        """
        层次遍历
        :param root: 根节点
        :return: list_node -> List
        """

        queue_node = [root]  # 队列
        list_node = []  # 中序遍历存放结果列表

        while queue_node:  # 队列不为空,一直循环

            node = queue_node.pop()  # 出队
            if not node:  # 节点为空, 从头开始, 不把空节点放入结果列表
                continue
            list_node.append(node.val)  # 把节点数值存放到结果列表
            queue_node.insert(0, node.left)  # 左节点先入队
            queue_node.insert(0, node.right)  # 右节点后入队

        print(list_node)
        return list_node


class Solution:
    def levelOrderBottom(self, root):
        """
        先序遍历
        :param root: 根节点
        :return: list_node -> List
        """
        stack_node = [root]  # 栈
        list_node = []  # 先序遍历结果存放列表

        while stack_node:  # 栈不为空
            node = stack_node.pop()  # 栈顶节点出栈
            if not node:  # 节点为空
                continue
            list_node.append(node.val)  # 把不为空的节点数值存到列表
            stack_node.append(node.right)  # 右节点先压栈
            stack_node.append(node.left)  # 左节点后压栈
        print(list_node)
        return list_node

    def preOrderBottom_re(self, root):
        """
        先序遍历 递归
        :param root: 根节点
        :return: list_node -> List
        """

        if not root:
            return None
        print(root.val)
        self.preOrderBottom_re(root.left)
        self.preOrderBottom_re(root.right)


class Solution:
    def levelOrderBottom(self, root):
        """
        中序遍历 非递归
        :param root:  根节点
        :return: list_node -> List
        """
        stack_node = []  # 栈
        list_node = []  # 中序遍历结果存放列表
        node_p = root  # 当前节点
        while stack_node or node_p:  # 当前节点不为空 or 栈不为空

            while node_p:  # 一直移动到最左端
                stack_node.append(node_p)  # 节点压栈
                node_p = node_p.left  # 指针左移

            node = stack_node.pop()  # 出栈
            list_node.append(node.val)  # 获取节点数据
            node_p = node.right  # 获取右节点
        print(list_node)
        return list_node

    def inOrderBottom_re(self, root):
        """
        中序遍历 递归
        :param root: 根节点
        :return: list_node -> List
        """

        if not root:
            return None
        self.inOrderBottom_re(root.left)
        print(root.val)
        self.inOrderBottom_re(root.right)


class Solution:
    def levelOrderBottom(self, root):
        """
        后序遍历 非递归
        :param root: 根节点
        :return: list_node -> List
        """
        stack_node = [root]
        list_node = []

        while stack_node:
            node = stack_node.pop()

            if node.left:  # 左孩子不为空
                stack_node.append(node.left)  # 左孩子压栈
            if node.right:  # 右孩子不为空
                stack_node.append(node.right)  # 右孩子压栈

            list_node.append(node.val)  # 获取当前指针数值

        list_node.reverse()  # 取反
        return list_node

    def postOrderBottom_re(self, root):
        """
        后序遍历 递归
        :param root: 根节点
        :return: list_node -> List
        """

        if not root:
            return None
        self.postOrderBottom_re(root.left)
        self.postOrderBottom_re(root.right)
        print(root.val)
