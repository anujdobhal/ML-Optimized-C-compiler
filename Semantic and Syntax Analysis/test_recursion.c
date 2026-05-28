int val = 5;

int recurse()
{
    if (val > 0)
    {
        val = val - 1;
        recurse();
    }
    return val;
}

int main()
{
    recurse();
    return 0;
}
