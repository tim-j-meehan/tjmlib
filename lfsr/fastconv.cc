#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT> // Eigen FFT module

// Function to compute convolution using FFT
Eigen::VectorXd fastConvolution(const Eigen::VectorXd& signal, const Eigen::VectorXd& kernel) {
    Eigen::FFT<double> fft;

    // Determine the size for zero-padding (next power of 2 of combined length)
    int n = signal.size() + kernel.size() - 1;
    int nPadded = std::pow(2, std::ceil(std::log2(n)));

    // Zero-pad the signal and kernel
    Eigen::VectorXd signalPadded = Eigen::VectorXd::Zero(nPadded);
    Eigen::VectorXd kernelPadded = Eigen::VectorXd::Zero(nPadded);

    signalPadded.head(signal.size()) = signal;
    kernelPadded.head(kernel.size()) = kernel;

    // Perform FFT on both padded vectors
    std::vector<std::complex<double>> signalFFT, kernelFFT;
    fft.fwd(signalFFT, signalPadded);
    fft.fwd(kernelFFT, kernelPadded);

    // Multiply in the frequency domain
    std::vector<std::complex<double>> resultFFT(nPadded);
    for (int i = 0; i < nPadded; ++i) {
        resultFFT[i] = signalFFT[i] * kernelFFT[i];
    }

    // Inverse FFT to get the convolution result
    Eigen::VectorXd result;
    fft.inv(result, resultFFT);

    // Truncate to the valid convolution size
    return result.head(n);
}

int main() {
    // Example signal and kernel
    Eigen::VectorXd signal(5);
    Eigen::VectorXd kernel(3);

    signal << 1.0, 2.0, 3.0, 4.0, 5.0;
    kernel << 0.2, 0.5, 0.2;

    // Perform fast convolution
    Eigen::VectorXd result = fastConvolution(signal, kernel);

    // Display the result
    std::cout << "Signal: " << signal.transpose() << "\n";
    std::cout << "Kernel: " << kernel.transpose() << "\n";
    std::cout << "Convolution result: " << result.transpose() << "\n";

    return 0;
}
