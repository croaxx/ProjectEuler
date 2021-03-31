# Problem description: https://contest.yandex.ru/contest/19036/problems/B/
# Solution complexity: time - O(NlogN), space - O(N).

# Solution:
# 1) As the problem states, there are N alarms, which ring every X minutes after
#    their starting time. Therefore, if an alarm starts ringing at some time ti,
#    then it will ring at: ti, ti + X, ti + 2*X, ti + 3*X, ..., . It is also said
#    that if more than one alarm ring at the same time, only one of them is
#    counted. So the first subtask is to remove the duplicate alarms and leave
#    only those ones, which ring at unique time moments. Two alarms starting at
#    ti and tj will have overlapping ringing times if (ti mod X) == (tj mod X).
#    An alarm with a smaller starting time should be kept and the other one can
#    be safely removed, as it will ring at exactly same time moments (and thus
#    is not counted by the problem definition). We can iterate over all starting
#    times ti of the alarms and build a hash_map with keys := (ti mod X) and 
#    values := min(ti, hash_map[ti mod X]), keeping the smallest times as values.

# 2) After the step 1) we have an array (let's call it `start_times`) of size
#    N'<=N, containing unique starting times of the alarms and importantly their
#    ringing times do not overlap at any future time moment.
#    We have two possible scenarios: 
#    a) N'>=K, where K is the total number of alarms to be heard before the
#       programmer wakes up. We can build a priority queue (binary heap) in O(N')
#       from this unique `start_times` array. Then we just keep popping and
#       pushing new values from/to this heap and do it K-times in total. When a
#       value with tj is popped from the heap, we re-insert a new value tj+X,
#       as it's the next time that this alarm will ring. The wake up time
#       corresponds to the last value extracted from the heap. The overall time
#       complexity is thus O(KlogN)=O(N'logN')=O(NlogN), as N'>=K.
#     b) N'<K.
#        Here the situation is slightly different. Firstly, we can find the 
#        maximum time in the array of `start_times`, let's call it t_max. We can
#        easily count in O(N') how many alarms rang before this t_max, let's call
#        it `rings_before_tmax`. Moreover, we know that in the time period
#        (t_max, t_max + X] exactly N' alarms will ring, let's call it
#        `rings_in_period`. It means that we can also easily count how many such
#        periods are necessary, before the required K alarms ring. After that we
#        can compute how many alarms remain to ring before we reach K:
#        rings_remain = K - rings_before_tmax - rings_in_period * num_periods.
#        To compute the final wake up time, we can use the same approach with
#        priority queue as in a). But instead we build the heap with values 
#        corresponding to `rings_remain` times.

import heapq

def process_alarms_starting_times(X: int, all_start_times: list) -> list:
    map_modulo = {}
    inf = 10E+14
    for time in all_start_times:
        modulo = time % X
        map_modulo[modulo] = min(time, map_modulo.get(modulo, inf))
    return list(map_modulo.values())

def compute_wake_time(X: int, K: int, start_times: list) -> int:
    time_max = max(start_times)
    rings_before_tmax = sum([(time_max - t) // X + 1 for t in start_times])
    rings_remain = K
    wake_time = 0
    heap = []
    if rings_before_tmax > K:
        heap = list(start_times)
    else:
        rings_in_period = len(start_times)
        num_periods = (K - rings_before_tmax) // rings_in_period
        rings_remain = K - rings_before_tmax - rings_in_period * num_periods
        wake_time = time_max + X * num_periods
        heap = [
            X * num_periods + t + X * ((time_max + X - t) // X) 
            for t in start_times
        ]
    heapq.heapify(heap)
    while rings_remain > 0:
        wake_time = heap[0]
        heapq.heappop(heap)
        heapq.heappush(heap, wake_time + X)
        rings_remain -= 1
    return wake_time


def main():
    N, X, K = map(int, input().split(' '))
    all_start_times = list(map(int, input().split(' ')))
    
    start_times = process_alarms_starting_times(X, all_start_times)
    wake_time = compute_wake_time(X, K, start_times)

    print(wake_time)

if __name__ == "__main__":
    main()