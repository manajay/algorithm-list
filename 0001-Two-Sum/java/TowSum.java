import java.util.HashMap;

/**
 *
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * Example:
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 *
 *
 * @author ljtwan
 * @date 2019/3/17
 **/
public class TowSum {

    public static int[] solution(int[] nums, int target) {
        if (nums.length < 2){
            return nums;
        }

        int ret[] = new int[2];
        HashMap<Integer, Integer> hashMap = new HashMap();

        for (int i = 0; i < nums.length; i++) {
            int other = target - nums[i];
            Integer num = hashMap.get(other);
            if (num != null) {
                if (i <= num) {
                    ret[0] = i;
                    ret[1] = num;
                } else {
                    ret[0] = num;
                    ret[1] = i;
                }
                break;
            } else {
                hashMap.put(nums[i],i);
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        int nums[] =  {3,3};
        int target = 6;
        int[] solution = TowSum.solution(nums, target);

        System.out.println("----------------");
        for (int n: solution) {
            System.out.println(n);
        }
        System.out.println("----------------");
    }
}
