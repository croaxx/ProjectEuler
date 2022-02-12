// Problem description: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Time complexity: O(const^n), n=len(digits) - generate all combinations
// Space complexity: O(const^n) - store all combinations

use std::{collections::HashMap, iter::FromIterator};

pub struct Solution {}

impl Solution {
    pub fn letter_combinations(digits: String) -> Vec<String> {
        let solver = Solver::new(digits.as_str());
        let results = solver.solve();
        results
    }
}

pub struct Solver {
    phone_map: HashMap<u8, Vec<char>>,
    digits: Vec<u8>,
}

impl Solver {
    pub fn new(digits: &str) -> Self {
        let phone_map: HashMap<_, _> = HashMap::from_iter([
            (2, vec!['a', 'b', 'c']),
            (3, vec!['d', 'e', 'f']),
            (4, vec!['g', 'h', 'i']),
            (5, vec!['j', 'k', 'l']),
            (6, vec!['m', 'n', 'o']),
            (7, vec!['p', 'q', 'r', 's']),
            (8, vec!['t', 'u', 'v']),
            (9, vec!['w', 'x', 'y', 'z']),
        ]);
        Self {
            digits: digits
                .chars()
                .map(|x| x.to_digit(10).unwrap() as u8)
                .collect::<Vec<_>>(),
            phone_map,
        }
    }

    pub fn solve(&self) -> Vec<String> {
        let mut result = Vec::new();
        let mut combination = String::new();
        self.assemble_combinations(&mut combination, &mut result);
        result
    }

    pub fn assemble_combinations(&self, combination: &mut String, combinations: &mut Vec<String>) {
        let idx = combination.len();
        if idx == self.digits.len() {
            if combination != "" {
                combinations.push(combination.to_owned());
            }
            return;
        }
        for ch in self.phone_map.get(&self.digits[idx]).unwrap() {
            combination.push(*ch);
            self.assemble_combinations(combination, combinations);
            combination.pop();
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::Solution;

    #[test]
    fn letter_combinations_success() {
        let digits: String = "23".to_owned();
        let result = Solution::letter_combinations(digits);
        assert_eq!(
            result,
            vec!["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
        );
    }

    #[test]
    fn letter_combinations_success_2() {
        let digits: String = "".to_owned();
        let result = Solution::letter_combinations(digits);
        assert_eq!(result.len(), 0);
    }
}
