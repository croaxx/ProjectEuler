/*
Problem description: https://contest.yandex.ru/contest/19036/problems/B/
Solution complexity: time - O(NlogN), space - O(N).

Solution:
1) As the problem states, there are N alarms, which ring every X minutes after
   their starting time. Therefore, if an alarm starts ringing at some time ti,
   then it will ring at: ti, ti + X, ti + 2*X, ti + 3*X, ..., . It is also said
   that if more than one alarm ring at the same time, only one of them is
   counted. So the first subtask is to remove the duplicate alarms and leave
   only those ones, which ring at unique time moments. Two alarms starting at
   ti and tj will have overlapping ringing times if (ti mod X) == (tj mod X).
   An alarm with a smaller starting time should be kept and the other one can
   be safely removed, as it will ring at exactly same time moments (and thus
   is not counted by the problem definition). We can iterate over all starting
   times ti of the alarms and build a hash_map with keys := (ti mod X) and 
   values := min(ti, hash_map[ti mod X]), keeping the smallest times as values.

2) After the step 1) we have an array (let's call it `start_times`) of size
   N'<=N, containing unique starting times of the alarms and importantly their
   ringing times do not overlap at any future time moment.
   We have two possible scenarios: 
   a) N'>=K, where K is the total number of alarms to be heard before the
      programmer wakes up. We can build a priority queue (binary heap) in O(N')
      from this unique `start_times` array. Then we just keep popping and
      pushing new values from/to this heap and do it K-times in total. When a
      value with tj is popped from the heap, we re-insert a new value tj+X,
      as it's the next time that this alarm will ring. The wake up time
      corresponds to the last value extracted from the heap. The overall time
      complexity is thus O(KlogN)=O(N'logN')=O(NlogN), as N'>=K.
    b) N'<K.
       Here the situation is slightly different. Firstly, we can find the 
       maximum time in the array of `start_times`, let's call it t_max. We can
       easily count in O(N') how many alarms rang before this t_max, let's call
       it `rings_before_tmax`. Moreover, we know that in the time period
       (t_max, t_max + X] exactly N' alarms will ring, let's call it
       `rings_in_period`. It means that we can also easily count how many such
       periods are necessary, before the required K alarms ring. After that we
       can compute how many alarms remain to ring before we reach K:
       rings_remain = K - rings_before_tmax - rings_in_period * num_periods.
       To compute the final wake up time, we can use the same approach with
       priority queue as in a). But instead we build the heap with values 
       corresponding to `rings_remain` times.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using LongInt = long long int;

void read_inputs_from_stdin(LongInt& N,
                            LongInt& X,
                            LongInt& K,
                            vector<LongInt>& all_start_times)
{
    scanf("%lld %lld %lld", &N, &X, &K);
    LongInt time;
    for (int i = 0; i < N; ++i) {
        scanf("%lli", &time);
        all_start_times.push_back(time);
    }
}

void process_alarms_starting_times(LongInt X,
                                   LongInt& time_max,
                                   const vector<LongInt>& all_start_times,
                                   vector<LongInt>& start_times)
{
    // hash map to select unique and non-overlapping alarms start times.
    unordered_map<LongInt, LongInt> map_modulo;
    for (auto time : all_start_times) {
        LongInt modulo = time % X;
        auto it = map_modulo.find(modulo);
        if (it == end(map_modulo)) {
            map_modulo.emplace(modulo, time);
        } else {
            it->second = min(it->second, time);
        }
    }
    for (auto e : map_modulo) {
        LongInt time = e.second;
        start_times.push_back(time);
        time_max = max(time_max, time);
    }
}

LongInt compute_wake_time(LongInt K, 
                          LongInt X,
                          LongInt time_max,
                          vector<LongInt>& start_times)
{
    LongInt rings_before_tmax = 0;
    LongInt rings_remain = 0;
    LongInt wake_time = 0;
    // default is max-heap, so we insert negative values to make it min-heap
    vector<LongInt> pq;  
    for (auto t : start_times) {
        rings_before_tmax += ((time_max - t) / X) + 1;
    }
    if (rings_before_tmax > K) {
        rings_remain = K;
        for (auto time : start_times) {
            pq.emplace_back(-time);
        }
    } else {
        LongInt rings_in_period = (LongInt)start_times.size();
        LongInt num_periods = (K - rings_before_tmax) / rings_in_period;
        rings_remain = K - rings_before_tmax - rings_in_period * num_periods;
        wake_time = time_max + X * num_periods;
        for (auto t : start_times) {
            LongInt time = t + X * num_periods + X * ((time_max + X - t) / X);
            pq.emplace_back(-time);
        }
    }
    make_heap(begin(pq), end(pq));
    while (rings_remain > 0) {
        wake_time = -pq.front();
        pop_heap(begin(pq), end(pq));
        pq.pop_back();
        pq.emplace_back(-wake_time - X);
        push_heap(begin(pq), end(pq));
        --rings_remain;
    }
    return wake_time;
}

int main()
{
    LongInt N, X, K, time_max = -1;
    vector<LongInt> all_start_times, start_times;

    read_inputs_from_stdin(N, X, K, all_start_times);
    process_alarms_starting_times(X, time_max, all_start_times, start_times);
    LongInt wake_time = compute_wake_time(K, X, time_max, start_times);

    printf("%lld\n", wake_time);
    return 0;
}