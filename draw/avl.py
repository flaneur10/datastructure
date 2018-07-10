#!/usr/bin/python3

from graphviz import Digraph,nohtml

class Node:
    """
    Node class!
    Attributes:
    data:the value of the node.
    lchild:left child of the node.
    rchild:right child of the node.
    number:the order number of the node.
    """
    def __init__(self,data,number=None,lchild=None,rchild=None):
        self.data=data
        self.lchild=lchild
        self.rchild=rchild
        self.number=number
class Tree:
    """
    Tree class!
    """
    def __init__(self,data=None):
        """
        To initialize a root node with a given value(default by None) and number is 0 by default.
        """
        node=Node(data,0)
        self.root=node
    def addnode(self,parent,child,flag=-1):
        """
        To add a new node to current tree.
        Parameters:
            parent:parent node.
            child:child node.
            flag:flag for l/r(0 for left and 1 for right)
        Return:
            True.
        """
        assert flag>=0,"Positon of child not defined"
        if flag==0:
            assert parent.lchild==None,"Left child exists"
            parent.lchild=child
        elif flag==1:
            assert parent.rchild==None,"Right child exists"
            parent.rchild=child
        else:
            raise ValueError("Wrong flag!")
        return True
    def plotTree(self):
        """
        To plot the tree.
        """
        dot = Digraph('dot',filename="A tmp Table",node_attr={'shape':'record','height':'.1'})
        Nodetmp=self.root
        def createnode(node,Dot):
            Dot.node('node{}'.format(str(node.number)),nohtml('<f0> |<f1> {}|<f2>'.format(str(node.data))))
            if node.lchild!=None:
                createnode(node.lchild,Dot)
            if node.rchild!=None:
                createnode(node.rchild,Dot)
        def connect(node,Dot):
            if node.lchild!=None:
                Dot.edge('node{}:f0'.format(str(node.number)),'node{}:f1'.format(str(node.lchild.number)))
                connect(node.lchild,Dot)
            if node.rchild!=None:
                Dot.edge('node{}:f2'.format(str(node.number)),'node{}:f1'.format(str(node.rchild.number)))
                connect(node.rchild,Dot)
        createnode(Nodetmp,dot)
        connect(Nodetmp,dot)
        print(dot.source)
        dot.render('file/figure', view=True)
def findnode(node,num):
    if node.number==num:
        return node,True
    if node.lchild!=None:
        rnode,rflag=findnode(node.lchild,num)
        if rflag:
            return rnode,rflag
    if node.rchild!=None:
        rnode,rflag=findnode(node.rchild,num)
        if rflag:
            return rnode,rflag
    return node,False

def init():
    """
    To draw the binary tree!
    Parameters that you need to input:
        value of root:the root to be initialized and the value you give.
        flag of new node:0 for left and 1 for right.
        number of parent:the number of the parent of your new node.
        value of new node:...
    Note:1)input -1 to stop inputing any new nodes and output the result!
         2)You can use pre-order to number these nodes.
    """
    rdata=input("Please input the value of root:")
    tree=Tree(rdata)
    while True:
        num_str=input("Input the number of the next node(-1 to stop and output):")
        num=int(num_str)
        if num==-1:
            break
        data=input("Input the value of new node:")
        flag=int(input("Input the flag of new node:"))
        parent_num=int(input("Input the number of parent node:"))
        tmpnode=Node(data,num)
        parent_node,Flag=findnode(tree.root,parent_num)
        if Flag==False:
            print("No such a node in current tree!")
            continue
        tree.addnode(parent_node,tmpnode,flag)
    tree.plotTree()

if __name__=="__main__":
    """
    mytree=Tree("A")
    B=Node("B",1)
    C=Node("C",2)
    D=Node("D",3)
    E=Node("E",4)
    F=Node("F",5)
    G=Node("G",6)
    mytree.addnode(mytree.root,B,0)
    mytree.addnode(B,C,0)
    mytree.addnode(B,D,1)
    mytree.addnode(D,E,0)
    mytree.addnode(D,F,1)
    mytree.addnode(E,G,1)
    mytree.plotTree()
    """
    init()







