// Problem description: https://projecteuler.net/problem=185
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using static System.Console;

namespace Task_185
{
    using vi = List<int>;
    using vvi = List<List<int>>;
    using CombinationSets = Dictionary<int, List<List<int>>>;

    class Program
    {
        static void Main()
        {
            var sw = new Stopwatch();
            sw.Start();

            var sets = GenerateAllSets();
            vi number = Enumerable.Repeat(-1, GuessAttempts.Guess[0].Count).ToList();
            BacktrackGuess(sets, number, 0);

            sw.Stop();

            WriteLine("Elapsed = {0}", sw.Elapsed);
        }

        private static void BacktrackGuess(CombinationSets sets, vi number, int guessIteration)
        {
            if (guessIteration == GuessAttempts.Guess.Count)
            {
                PrintNumber(number);
                return;
            }

            sets.TryGetValue(GuessAttempts.RemainCorrectGuesses[guessIteration],
                             out var comb);

            if (comb == null)
            {
                BacktrackGuess(sets, number, guessIteration + 1);
                return;
            }

            for (int i = 0; i < comb.Count; ++i)
            {
                var initialNumber = number.Select(c => c).ToList();
                bool resSet = TrySetNewDigits(number, comb[i], guessIteration);

                if (resSet)
                {
                    var initRemainCorrect = GuessAttempts.RemainCorrectGuesses.Select(c=>c).ToList();
                    var initGuesses = GuessAttempts.Guess.Select(c => c.ToList()).ToList();

                    bool legitimate = TryUpdateCorrectGuesses(number, comb[i]);

                    if (legitimate)
                    {
                        BacktrackGuess(sets, number, guessIteration + 1);
                    }

                    GuessAttempts.RemainCorrectGuesses = initRemainCorrect;
                    GuessAttempts.Guess = initGuesses;
                }

                number = initialNumber;
            }
        }

        private static void PrintNumber(vi number)
        {
            Write("Candidate number: ");
            foreach (var n in number)
            {
                if (n == -1) Write($"*");
                else Write(n);
            }
            WriteLine();
        }

        private static bool TryUpdateCorrectGuesses(vi number, vi comb)
        {
            for (int g = 0; g < GuessAttempts.Guess.Count; ++g)
            {
                for (int j = 0; j < comb.Count; ++j)
                {
                    if (GuessAttempts.Guess[g][comb[j]] == number[comb[j]])
                    {
                        --GuessAttempts.RemainCorrectGuesses[g];
                        GuessAttempts.Guess[g][comb[j]] = -1;
                    }

                    if (GuessAttempts.RemainCorrectGuesses[g] < 0)
                        return false;
                }
            }

            int maxRemainGuesses = GuessAttempts.RemainCorrectGuesses.Max();
            if (maxRemainGuesses > 0 && maxRemainGuesses > number.Count(c => c == -1))
                return false;

            return true;
        }

        private static bool TrySetNewDigits(vi number, vi indices, int guessIdx)
        {
            foreach (var idx in indices)
            {
                if (number[idx] == -1)
                    number[idx] = GuessAttempts.Guess[guessIdx][idx];
                else
                    return false;
            }
            return true;
        }

        private static CombinationSets GenerateAllSets()
        {
            int n = GuessAttempts.Guess[0].Count; // length of the number
            var ks = GuessAttempts.RemainCorrectGuesses.GroupBy(c => c)
                .Select(g => g.First())
                .Where(c => c != 0)
                .ToList();

            var dict = new CombinationSets();

            foreach (var k in ks)
            {
                var set = new vvi();
                GenerateSet_nk(n, k, new vi(), set);
                dict.Add(k, set);
            }

            return dict;
        }

        private static void GenerateSet_nk(int n, int k, vi comb, vvi set)
        {
            int size = comb.Count;

            if (size == k)
            {
                set.Add(size != 0 ? new vi(comb) : new vi());
                return;
            }

            int last = size == 0 ? -1 : comb[size - 1];

            for (int i = last + 1; i < size + n - k + 1; ++i)
            {
                comb.Add(i);
                GenerateSet_nk(n, k, comb, set);
                comb.RemoveAt(size);
            }
        }
    }

    public static class GuessAttempts
    {
        public static vvi Guess;

        public static vi RemainCorrectGuesses;

        private static readonly List<string> RawGuessInput = new List<string>() {
        {"5616185650518293"}, {"3847439647293047"}, {"5855462940810587"},
        {"9742855507068353"}, {"4296849643607543"}, {"3174248439465858"},
        {"4513559094146117"}, {"7890971548908067"}, {"8157356344118483"},
        {"2615250744386899"}, {"8690095851526254"}, {"6375711915077050"},
        {"6913859173121360"}, {"6442889055042768"}, {"2321386104303845"},
        {"2326509471271448"}, {"5251583379644322"}, {"1748270476758276"},
        {"4895722652190306"}, {"3041631117224635"}, {"1841236454324589"},
        {"2659862637316867"}};

        private static readonly vi CorrectGuessesInitial = new vi() {
            2, 1, 3, 3, 3, 1, 2, 3, 1, 2, 3,
            1, 1, 2, 0, 2, 2, 3, 1, 3, 3, 2 };

        static GuessAttempts()
        {
            ParseRawInputToArrays();
            RemainCorrectGuesses = new vi(CorrectGuessesInitial);
        }

        private static void ParseRawInputToArrays()
        {
            Guess = new vvi();

            foreach (string t in RawGuessInput)
                Guess.Add(t.Select(x => x - '0').ToList());
        }
    }
}

