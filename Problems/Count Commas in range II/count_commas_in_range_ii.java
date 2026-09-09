class Solution {
    public long countCommas(long n) {
        long commas = 0;
        long treshold = 1000;

        while (n >= treshold) {
            commas += (long) (n - treshold + 1);
            treshold *= 1000;
        }

        return commas;
    }
}