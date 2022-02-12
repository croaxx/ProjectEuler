# Problem description: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
# Time complexity: O(const^n), n=len(digits) - generate all combinations
# Space complexity: O(const^n) - store all combinations


class Solution:
    phone_map = {
        "2": ["a", "b", "c"],
        "3": ["d", "e", "f"],
        "4": ["g", "h", "i"],
        "5": ["j", "k", "l"],
        "6": ["m", "n", "o"],
        "7": ["p", "q", "r", "s"],
        "8": ["t", "u", "v"],
        "9": ["w", "x", "y", "z"],
    }

    def assembleCombinations(self, combination: str, combinations: List[str]):
        idx = len(combination)
        if idx == len(self.digits):
            if combination:
                combinations.append("".join(combination))
            return
        for ch in Solution.phone_map[self.digits[idx]]:
            combination.append(ch)
            self.assembleCombinations(combination, combinations)
            combination.pop()

    def letterCombinations(self, digits: str) -> List[str]:
        self.digits = digits
        combinations, combination = [], []
        self.assembleCombinations(combination, combinations)
        return combinations
