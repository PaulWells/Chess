void FAIL_FAST(std::string message)
{
    std::cout << message;
    // Cause a crash to fail fast;
    int* x = nullptr;
    int y = *x;
}
