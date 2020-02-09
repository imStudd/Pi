#include "pi.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage ./pi <k> <n thread(s)>\n");
        exit(1);
    }

    unsigned int n(std::atoi(argv[1]));
    unsigned int nThreads(std::atoi(argv[2]));

    std::vector<std::thread> vecThreads;
    std::vector<mpf_class> res(nThreads, mpf_class(0, n * PRECISION));

    mpf_class pi(0, n * PRECISION);

    for (unsigned int i(0); i < nThreads; ++i) {
        vecThreads.emplace_back(bbp, n, i, nThreads, std::ref(res[i]));
    }

    for (size_t i(0); i < vecThreads.size(); ++i) {
        vecThreads[i].join();
    }

    for (size_t i(0); i < res.size(); ++i) {
        pi += res[i];
    }

    writeOutputFile(n, pi);

    // std::cout << std::setprecision(n) << pi << std::endl;
    return 0;
}

void bbp(unsigned int n, unsigned int start, unsigned int step, mpf_class& res) {
    unsigned long long prec(n * PRECISION);
    mpf_class pi(0, prec),
        s1(0, prec),
        s2(0, prec),
        s3(0, prec),
        s4(0, prec),
        e1(1.0, prec),
        e2(2.0, prec),
        e4(4.0, prec),
        e5(5.0, prec),
        e6(6.0, prec),
        e8;

    mpf_t pow_;
    mpf_init2(pow_, prec);

    for (unsigned int k(start); k < n; k += step) {
        mpf_set_d(pow_, 16.0);
        mpf_pow_ui(pow_, pow_, k);
        mpf_class pow(pow_, prec);

        e8 = (mpf_class(8.0, prec) * mpf_class(k, prec));

        s1 = (e4 / (e8 + e1));
        s2 = (e2 / (e8 + e4));
        s3 = (e1 / (e8 + e5));
        s4 = (e1 / (e8 + e6));

        pi += (e1 / pow) * (s1 - s2 - s3 - s4);
    }

    res = pi;
}

void writeOutputFile(unsigned int prec, mpf_class& pi) {
    std::ofstream file("results_16705068.txt");
    std::string buf;

    mp_exp_t t;
    buf.append(pi.get_str(t));
    buf.insert(1, ".");
    file.write(buf.data(), prec);
    file.close();
}
