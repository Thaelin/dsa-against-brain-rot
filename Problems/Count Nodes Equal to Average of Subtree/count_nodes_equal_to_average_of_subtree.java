class Solution {

    public class TreeNode {
      int val;
      TreeNode left;
      TreeNode right;
      TreeNode() {}
      TreeNode(int val) { this.val = val; }
      TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
      }
    }
    
    public record Stats(int sum, int count, int matches) {}
    
    public int averageOfSubtree(TreeNode root) {
        var stats = countStats(root);
        
        return stats.matches();
    }
    
    private Stats countStats(TreeNode node) {
        if (node == null) {
            return new Stats(0, 0, 0);
        }
        
        Stats left = countStats(node.left);
        Stats right = countStats(node.right);
        
        int sum = left.sum() + right.sum() + node.val;
        int count = left.count() + right.count() + 1;
        int average = sum / count;
        int matches = left.matches() + right.matches();
        
        return new Stats(sum, count, average == node.val ? matches + 1 : matches);
    }
}