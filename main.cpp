#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <time.h>

using namespace std;

const int MAX_SIZE = 16;

class CheckoutLine
{
public:
    CheckoutLine() { m_size = 0; }

    void push(int customer)
    {
        if (m_size == MAX_SIZE - 1)
        {
            cout << "Stack overflow" << endl;
            return;
        }
        arr[m_size++] = customer;
    }

    int pop()
    {
        if (m_size == 0)
        {
            cout << "Stack underflow" << endl;
            return -1;
        }
        
        int tmp = arr[0];
        for (int i = 1; i < m_size; ++i)
        {
            arr[i-1] = arr[i];
        }
        m_size--;
        return tmp;
    }

    int size() { return m_size; }

private:
    int arr[MAX_SIZE];
    int m_size;
};

class Supermarket
{
public:
    Supermarket(int duration)
    {
        this->duration = duration;
        time = 0;
        serve_time = 0;
        served = 0;

        total_wait_time = 0;
        longest_wait_time = 0;

        total_line_length = 0;
        longest_line_length = 0;
    }

    void simulate()
    {
        while (!closed())
        {
            if (time < duration && rand() % 100 < 25)
            {
                line.push(time);
            }

            if (serve_time == 0 && line.size() > 0)
            {
                int wait_time = time - line.pop();
                total_wait_time += wait_time;
                longest_wait_time = max(wait_time, longest_wait_time);
                served++;
            }

            if (serve_time <= 0 && line.size() > 0)
            {
                serve_time = rand() % 4 + 1;
            }

            total_line_length += line.size();
            longest_line_length = max(line.size(), longest_line_length);

            time++;
            serve_time--;
        }
    }

    int customers_served() { return served; }
    float avg_wait() { return (float) total_wait_time / served; }
    int longest_wait() { return longest_wait_time; }
    float avg_line_len() { return (float) total_line_length / time; }
    int longest_line_len() { return longest_line_length; }

private:
    CheckoutLine line;

    int duration;
    int time;
    int serve_time;
    int served;

    int total_wait_time;
    int longest_wait_time;

    int total_line_length;
    int longest_line_length;

    bool closed() { return time >= duration && line.size() == 0; }
};

int main()
{
    srand(time(NULL));
    Supermarket supermarket = Supermarket(720);
    supermarket.simulate();

    cout << fixed << setprecision(1);
    cout << "Customers served: " << supermarket.customers_served() << endl;
    cout << "Average wait time: " << supermarket.avg_wait() << endl;
    cout << "Longest wait time: " << supermarket.longest_wait() << endl;
    cout << "Average line length: " << supermarket.avg_line_len() << endl;
    cout << "Longest line length: " << supermarket.longest_line_len() << endl;

    return 0;
}
