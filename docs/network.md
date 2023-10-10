# Network

```c++
int main()
{
    try
    {
        UdpServer server(4242);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```
