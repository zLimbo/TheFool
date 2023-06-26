

auto f(auto x) {
    return static_cast<double>(x);
}

int main() {

    auto x = f(3);

    return 0;
}