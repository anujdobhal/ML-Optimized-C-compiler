int main()
{
    int i = 0;
    int sum = 0;
    int val = 10;

    for (i = 0; i < 5; i = i + 1)
    {
        if (i < 3)
        {
            sum = sum + val;
        }
        else
        {
            sum = sum - val;
        }

        while (val > 8)
        {
            val = val - 1;
        }
    }

    return sum;
}
