#include <stdio.h>
int wait[1000];
int main() {
    int time, clock, num, end = 0, front = 0, in_queue = 0, window = 3, spare = 3; // index实际需要+1
    double wait_avrg = 0;
    scanf("%d", &time);
    for (clock = 1; clock <= time || front != end; clock++) { // 新的周期开始，上一周期的客户已全部离开。
        if (front < end) {                                    // 如果队中还有人，
            in_queue = end - front + 1;                       // 计算队中人数，
            wait_avrg = (double)in_queue / window;            // 计算平均等待人数，
            if (wait_avrg < 7 && window > 3 /*&& (double) in_queue / (window - 1) < 6*/) { // 如果平均等待人数小于7且窗口数大于3
                window--;                                     // 关闭一个窗口。
                wait_avrg = (double)in_queue / window;        // 保存平均等待人数，
                if (wait_avrg < 7 && window > 3 /*&& (double) in_queue / (window - 1) < 6*/) { // 如果窗口数大于3
                    window--;                                 // 再关闭一个窗口。
                }
            }
            if (in_queue > window) {                          // 如果队中人数大于窗口数，
                front += window;                              // 前面的出队接受服务，
                in_queue -= window;                           // 队中人数减少，
                spare = 0;                                    // 没有空闲窗口；
            } else {                                          // 如果队中人数小于或等于窗口数，
                if (clock <= time)
                    front = ++end;                            // 全部出队接受服务后，序号要后移一个
                else
                    front = end;
                spare = window - in_queue;                    // 可能还有空闲窗口，
                in_queue = 0;                                 // 但队中没人。
            }
        }
        if (clock <= time) {
            scanf("%d", &num);                                // 新客户到达。
            if (num > spare) {                                // 如果到达人数多于空闲窗口数，
                front += spare;                               // （可能没有空闲窗口）
                end = front + in_queue + num - spare - 1;     // 多余人需要排队，
                spare = 0;                                    // 没有空闲窗口，
                for (int i = front; i <= end; i++) {
                    wait[i]++;                                // 所有排队者等待时间增加。
                }
                in_queue = end - front + 1;                   // 计算队中人数。
                wait_avrg = (double)in_queue / window;        // 计算平均等待人数，
                if (wait_avrg >= 6 && window < 5) {           // 如果平均等待人数大于或等于7且窗口没开满，
                    window++;                                 // 新开窗口，
                    wait[front++]--;                          // 队首的出队接受服务。
                    in_queue = end - front + 1;               // 计算队中人数。
                    wait_avrg = (double)in_queue / window;    // 计算平均等待人数，
                    if (wait_avrg >= 6 && window < 5) {       // 如果平均等待时间仍然大于或等于7且窗口没开满，
                        window++;                             // 再新开窗口，
                        wait[front++]--;                      // 队首的再出队接受服务。
                    }
                }
            } else {                                          // 如果到达人数小于或等于空闲窗口数，
                if (clock >= time)                            // 如果不再有新客户到达，
                    front = end += num - 1;                   // 全部直接接受服务，这些人也算排了队，但序号不再后移一个；
                else                                          // 如果还会有新客户到达，
                    front = end += num;                       // 全部直接接受服务，这些人也算排了队，序号后移一个。
                spare = window - in_queue;                    // 无论如何，可能还有空闲窗口，
                in_queue = 0;                                 // 但队中都没人。
            }
        } else if (in_queue) {                                // 如果不再有新客户到达，且队中还有人
            for (int i = front; i <= end; i++) {
                wait[i]++;                                    // 所有排队者等待时间增加。
            }
        }
    }
    for (int i = 0; i <= end; i++) {
        printf("%d : %d\n", i + 1, wait[i]);
    }
    return 0;
}