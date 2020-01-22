#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include "HEAAN.h"

namespace py = pybind11;

using namespace std;
using namespace NTL;

PYBIND11_MAKE_OPAQUE(complex<double>);
PYBIND11_MAKE_OPAQUE(double);
PYBIND11_MAKE_OPAQUE(NTL::ZZ);

using ComplexDouble = complex<double>;
using Double = double;
using ZZ = NTL::ZZ;

PYBIND11_MODULE(HEAAN, m)
{
	m.doc() = "HEAAN For Python.";

	py::class_<ZZ>(m, "ZZ")
		.def(py::init<>())
		.def("to_ZZ", [](std::int64_t t){
			ZZ a;
			a = NTL::to_ZZ(t);
			std::cout << a << "\n";
			return a;
		});

	// ComplexDouble
	py::class_<ComplexDouble>(m, "ComplexDouble")
		.def(py::init<>())
		.def("numpy", [](py::array_t<complex<double>> in) {
			complex<double> *out = new complex<double>[in.size()];
			py::buffer_info in_info = in.request();
			complex<double> *in_ptr = (complex<double> *)in_info.ptr;
			for (std::size_t i = 0; i < in_info.size; i++)
			{
				out[i] = in_ptr[i];
			}
			return out;
		});

	// Double
	py::class_<Double>(m, "Double")
		.def(py::init<>())
		.def("numpy", [](py::array_t<double> in) {
			double *out = new double[in.size()];
			py::buffer_info in_info = in.request();
			double *in_ptr = (double *)in_info.ptr;
			for (std::size_t i = 0; i < in_info.size; i++)
			{
				out[i] = in_ptr[i];
			}
			return out;
		});

	// TestScheme
	py::class_<TestScheme>(m, "TestScheme")
		// STANDARD TESTS
		.def("testEncrypt", &TestScheme::testEncrypt)
		.def("testEncryptSingle", &TestScheme::testEncryptSingle)
		.def("testAdd", &TestScheme::testAdd)
		.def("testMult", &TestScheme::testMult)
		.def("testiMult", &TestScheme::testiMult)
		// ROTATE & CONJUGATE TESTS
		.def("testRotateFast", &TestScheme::testRotateFast)
		.def("testConjugate", &TestScheme::testConjugate)
		// POWER & PRODUCT TESTS
		.def("testPowerOf2", &TestScheme::testPowerOf2)
		.def("testPower", &TestScheme::testPower)
		// FUNCTION TESTS
		.def("testInverse", &TestScheme::testInverse)
		.def("testLogarithm", &TestScheme::testLogarithm)
		.def("testExponent", &TestScheme::testExponent)
		.def("testExponentLazy", &TestScheme::testExponentLazy)
		.def("testSigmoid", &TestScheme::testSigmoid)
		.def("testSigmoidLazy", &TestScheme::testSigmoidLazy)
		// BOOTSTRAPPING TESTS
		.def("testBootstrap", &TestScheme::testBootstrap)
		.def("testBootstrapSingleReal", &TestScheme::testBootstrapSingleReal)
		.def("testWriteAndRead", &TestScheme::testWriteAndRead);

	// Scheme
	py::class_<Scheme>(m, "Scheme")
		.def(py::init<SecretKey &, Ring &, bool>(), py::arg(), py::arg(), py::arg("isSerialized") = false)
		// KEYS GENERATION
		.def("addEncKey", &Scheme::addEncKey)
		.def("addMultKey", &Scheme::addMultKey)
		.def("addConjKey", &Scheme::addConjKey)
		.def("addLeftRotKey", &Scheme::addLeftRotKey)
		.def("addRightRotKey", &Scheme::addRightRotKey)
		.def("addLeftRotKeys", &Scheme::addLeftRotKeys)
		.def("addRightRotKeys", &Scheme::addRightRotKeys)
		.def("addBootKey", &Scheme::addBootKey)
		// ENCODING & DECODING
		.def("encode", (void (Scheme::*)(Plaintext &, complex<double> *, long, long, long)) & Scheme::encode)
		.def("encode", (void (Scheme::*)(Plaintext &, double *, long, long, long)) & Scheme::encode)
		.def("decode", (complex<double> * (Scheme::*)(Plaintext &)) & Scheme::decode)
		.def("encodeSingle", (void (Scheme::*)(Plaintext &, complex<double>, long, long)) & Scheme::encodeSingle)
		.def("encodeSingle", (void (Scheme::*)(Plaintext &, double, long, long)) & Scheme::encodeSingle)
		.def("decodeSingle", (complex<double>(Scheme::*)(Plaintext &, double *, long, long, long)) & Scheme::decodeSingle)
		// ENCRYPTION & DECRYPTION
		.def("encryptMsg", (void (Scheme::*)(Ciphertext &, Plaintext &)) & Scheme::encryptMsg)
		.def("decryptMsg", (void (Scheme::*)(Plaintext &, SecretKey &, Ciphertext &)) & Scheme::decryptMsg)
		.def("encrypt", (void (Scheme::*)(Ciphertext &, complex<double> *, long, long, long)) & Scheme::encrypt)
		.def("encrypt", (void (Scheme::*)(Ciphertext &, double *, long, long, long)) & Scheme::encrypt)
		.def("encryptZeros", (void (Scheme::*)(Ciphertext &, long, long, long)) & Scheme::encryptZeros)
		.def("decrypt", (complex<double> * (Scheme::*)(SecretKey &, Ciphertext &)) & Scheme::decrypt)
		.def("encryptSingle", (void (Scheme::*)(Ciphertext &, complex<double>, long, long)) & Scheme::encryptSingle)
		.def("encryptSingle", (void (Scheme::*)(Ciphertext &, double, long, long)) & Scheme::encryptSingle)
		.def("decryptSingle", (complex<double>(Scheme::*)(SecretKey &, Ciphertext &)) & Scheme::decryptSingle)
		// HOMOMORPHIC OPERATIONS
		.def("negate", &Scheme::negate)
		.def("negateAndEqual", &Scheme::negateAndEqual)
		.def("add", &Scheme::add)
		.def("addAndEqual", &Scheme::addAndEqual)
		.def("addConst", (void (Scheme::*)(Ciphertext &, Ciphertext &, double, long)) & Scheme::addConst)
		.def("addConst", (void (Scheme::*)(Ciphertext &, Ciphertext &, RR &, long)) & Scheme::addConst)
		.def("addConst", (void (Scheme::*)(Ciphertext &, Ciphertext &, complex<double>, long)) & Scheme::addConst)
		.def("addConstAndEqual", (void (Scheme::*)(Ciphertext &, double, long)) & Scheme::addConstAndEqual)
		.def("addConstAndEqual", (void (Scheme::*)(Ciphertext &, RR &, long)) & Scheme::addConstAndEqual)
		.def("addConstAndEqual", (void (Scheme::*)(Ciphertext &, complex<double>, long)) & Scheme::addConstAndEqual)
		.def("sub", &Scheme::sub)
		.def("subAndEqual", &Scheme::subAndEqual)
		.def("subAndEqual2", &Scheme::subAndEqual2)
		.def("imult", &Scheme::imult)
		.def("idiv", &Scheme::idiv)
		.def("imultAndEqual", &Scheme::imultAndEqual)
		.def("idivAndEqual", &Scheme::idivAndEqual)
		.def("mult", &Scheme::mult)
		.def("multAndEqual", &Scheme::multAndEqual)
		.def("square", &Scheme::square)
		.def("squareAndEqual", &Scheme::squareAndEqual)
		.def("multByConst", (void (Scheme::*)(Ciphertext &, Ciphertext &, double, long)) & Scheme::multByConst)
		.def("multByConst", (void (Scheme::*)(Ciphertext &, Ciphertext &, complex<double>, long)) & Scheme::multByConst)
		.def("multByConstVec", &Scheme::multByConstVec)
		.def("multByConstVecAndEqual", &Scheme::multByConstVecAndEqual)
		.def("multByConstAndEqual", (void (Scheme::*)(Ciphertext &, double, long)) & Scheme::multByConstAndEqual)
		.def("multByConstAndEqual", (void (Scheme::*)(Ciphertext &, RR &, long)) & Scheme::multByConstAndEqual)
		.def("multByConstAndEqual", (void (Scheme::*)(Ciphertext &, complex<double>, long)) & Scheme::multByConstAndEqual)
		.def("multByPoly", &Scheme::multByPoly)
		.def("multByPolyNTT", &Scheme::multByPolyNTT)
		.def("multByPolyAndEqual", &Scheme::multByPolyAndEqual)
		.def("multByPolyNTTAndEqual", &Scheme::multByPolyNTTAndEqual)
		.def("multByMonomial", &Scheme::multByMonomial)
		.def("multByMonomialAndEqual", &Scheme::multByMonomialAndEqual)
		.def("leftShift", &Scheme::leftShift)
		.def("leftShiftAndEqual", &Scheme::leftShiftAndEqual)
		.def("doubleAndEqual", &Scheme::doubleAndEqual)
		.def("divByPo2", &Scheme::divByPo2)
		.def("divByPo2AndEqual", &Scheme::divByPo2AndEqual)
		// RESCALING
		.def("reScaleBy", &Scheme::reScaleBy)
		.def("reScaleTo", &Scheme::reScaleTo)
		.def("reScaleByAndEqual", &Scheme::reScaleByAndEqual)
		.def("reScaleToAndEqual", &Scheme::reScaleToAndEqual)
		.def("modDownBy", &Scheme::modDownBy)
		.def("modDownByAndEqual", &Scheme::modDownByAndEqual)
		.def("modDownTo", &Scheme::modDownTo)
		.def("modDownToAndEqual", &Scheme::modDownToAndEqual)
		// ROTATIONS & CONJUGATIONS
		.def("leftRotateFast", &Scheme::leftRotateFast)
		.def("rightRotateFast", &Scheme::rightRotateFast)
		.def("leftRotateFastAndEqual", &Scheme::leftRotateFastAndEqual)
		.def("rightRotateFastAndEqual", &Scheme::rightRotateFastAndEqual)
		.def("conjugate", &Scheme::conjugate)
		.def("conjugateAndEqual", &Scheme::conjugateAndEqual)
		// BOOTSTRAPPING
		.def("normalizeAndEqual", &Scheme::normalizeAndEqual)
		.def("coeffToSlotAndEqual", &Scheme::coeffToSlotAndEqual)
		.def("slotToCoeffAndEqual", &Scheme::slotToCoeffAndEqual)
		.def("exp2piAndEqual", &Scheme::exp2piAndEqual)
		.def("evalExpAndEqual", &Scheme::evalExpAndEqual)
		.def("bootstrapAndEqual", &Scheme::bootstrapAndEqual);

	// BootContext
	py::class_<BootContext>(m, "BootContext")
		.def(py::init<>())
		.def_readwrite("bnd1", &BootContext::bnd1)
		.def_readwrite("bnd2", &BootContext::bnd2)
		.def_readwrite("logp", &BootContext::logp);

	// Ring
	py::class_<Ring>(m, "Ring")
		.def(py::init<>())
		// Encode & Decode
		.def("arrayBitReverse", &Ring::arrayBitReverse)
		.def("EMB", &Ring::EMB)
		.def("EMBInvLazy", &Ring::EMBInvLazy)
		.def("EMBInv", &Ring::EMBInv)
		.def("encode", (void (Ring::*)(ZZ *, double *, long, long)) & Ring::encode)
		.def("encode", (void (Ring::*)(ZZ *, complex<double> *, long, long)) & Ring::encode)
		.def("decode", &Ring::decode)
		// CONTEXT
		.def("addBootContext", &Ring::addBootContext)
		// MULTIPLICATION
		.def("maxBits", &Ring::maxBits)
		.def("CRT", &Ring::CRT)
		.def("addNTTAndEqual", &Ring::addNTTAndEqual)
		.def("mult", &Ring::mult)
		.def("multNTT", &Ring::multNTT)
		.def("multDNTT", &Ring::multDNTT)
		.def("multAndEqual", &Ring::multAndEqual)
		.def("multNTTAndEqual", &Ring::multNTTAndEqual)
		.def("square", &Ring::square)
		.def("squareNTT", &Ring::squareNTT)
		.def("squareAndEqual", &Ring::squareAndEqual)
		// OTHER
		.def("mod", &Ring::mod)
		.def("modAndEqual", &Ring::modAndEqual)
		.def("negate", &Ring::negate)
		.def("negateAndEqual", &Ring::negateAndEqual)
		.def("add", &Ring::add)
		.def("addAndEqual", &Ring::addAndEqual)
		.def("sub", &Ring::sub)
		.def("subAndEqual", &Ring::subAndEqual)
		.def("subAndEqual2", &Ring::subAndEqual2)
		.def("multByMonomial", &Ring::multByMonomial)
		.def("multByMonomialAndEqual", &Ring::multByMonomialAndEqual)
		.def("multByConst", &Ring::multByConst)
		.def("multByConstAndEqual", &Ring::multByConstAndEqual)
		.def("leftShift", &Ring::leftShift)
		.def("leftShiftAndEqual", &Ring::leftShiftAndEqual)
		.def("doubleAndEqual", &Ring::doubleAndEqual)
		.def("rightShift", &Ring::rightShift)
		.def("rightShiftAndEqual", &Ring::rightShiftAndEqual)
		// ROTATION & CONJUGATION
		.def("leftRotate", &Ring::leftRotate)
		.def("conjugate", &Ring::conjugate)
		// SAMPLING
		.def("subFromGaussAndEqual", &Ring::subFromGaussAndEqual)
		.def("addGaussAndEqual", &Ring::addGaussAndEqual)
		.def("sampleZO", &Ring::sampleHWT)
		.def("sampleUniform2", &Ring::sampleUniform2);
	// DFT

	// RingMultiplier
	py::class_<RingMultiplier>(m, "RingMultiplier")
		.def(py::init<>())
		.def("primeTest", &RingMultiplier::primeTest)
		.def("NTT", &RingMultiplier::NTT)
		.def("INTT", &RingMultiplier::primeTest)
		.def("CRT", &RingMultiplier::CRT)
		.def("addNTTAndEqual", &RingMultiplier::addNTTAndEqual)
		.def("reconstruct", &RingMultiplier::reconstruct)
		.def("mult", &RingMultiplier::mult)
		.def("multNTT", &RingMultiplier::multNTT)
		.def("multDNTT", &RingMultiplier::multDNTT)
		.def("multAndEqual", &RingMultiplier::multAndEqual)
		.def("multNTTAndEqual", &RingMultiplier::multNTTAndEqual)
		.def("square", &RingMultiplier::square)
		.def("squareNTT", &RingMultiplier::squareNTT)
		.def("squareAndEqual", &RingMultiplier::squareAndEqual)
		.def("mulMod", &RingMultiplier::mulMod)
		.def("mulModBarrett", &RingMultiplier::mulModBarrett)
		.def("butt", &RingMultiplier::butt)
		.def("ibutt", &RingMultiplier::ibutt)
		.def("idivN", &RingMultiplier::idivN)
		.def("invMod", &RingMultiplier::invMod)
		.def("powMod", &RingMultiplier::powMod)
		.def("inv", &RingMultiplier::inv)
		.def("pow", &RingMultiplier::pow)
		.def("bitReverse", &RingMultiplier::bitReverse)
		.def("findPrimeFactors", &RingMultiplier::findPrimeFactors)
		.def("findPrimitiveRoot", &RingMultiplier::findPrimitiveRoot)
		.def("findMthRootOfUnity", &RingMultiplier::findMthRootOfUnity);

	// Ciphertext
	py::class_<Ciphertext>(m, "Ciphertext")
		.def(py::init<long, long, long>(), py::arg("logp") = 0, py::arg("logq") = 0, py::arg("n") = 0)
		.def(py::init<const Ciphertext &>())
		.def("copyParams", &Ciphertext::copyParams)
		.def("copy", &Ciphertext::copy)
		.def("free", &Ciphertext::free)
		.def_readwrite("logp", &Ciphertext::logp)
		.def_readwrite("logq", &Ciphertext::logq)
		.def_readwrite("n", &Ciphertext::n);

	// EvaluatorUtils
	py::class_<EvaluatorUtils>(m, "EvaluatorUtils")
		// RANDOM REAL AND COMPLEX NUMBERS
		.def_static("randomReal", &EvaluatorUtils::randomReal, py::arg("bound") = 1.0)
		.def_static("randomComplex", &EvaluatorUtils::randomComplex, py::arg("bound") = 1.0)
		.def_static("randomCircle", &EvaluatorUtils::randomCircle, py::arg("anglebound") = 1.0)
		.def_static("randomRealArray", &EvaluatorUtils::randomRealArray, py::arg(), py::arg("bound") = 1.0)
		.def_static("randomComplexArray", &EvaluatorUtils::randomComplexArray, py::arg(), py::arg("bound") = 1.0)
		// .def("randomComplexArray", [](long size, double bound = 1.0){ return EvaluatorUtils::randomComplexArray(size, bound);})
		.def_static("randomCircleArray", &EvaluatorUtils::randomCircleArray, py::arg(), py::arg("bound") = 1.0)
		// DOUBLE & RR <-> ZZ
		.def_static("scaleDownToReal", &EvaluatorUtils::scaleDownToReal)
		// .def_static("scaleUpToZZ", (static ZZ (EvaluatorUtils::*)(const double, const long)) &EvaluatorUtils::scaleUpToZZ);
		.def("scaleUpToZZ", [](const double x, const long logp) { return EvaluatorUtils::scaleUpToZZ(x, logp); })
		.def("scaleUpToZZ", [](const RR &x, const long logp) { return EvaluatorUtils::scaleUpToZZ(x, logp); })
		// ROTATIONS
		.def_static("leftRotateAndEqual", &EvaluatorUtils::leftRotateAndEqual)
		.def_static("rightRotateAndEqual", &EvaluatorUtils::rightRotateAndEqual);

	// SchemeAlgo
	py::class_<SchemeAlgo>(m, "SchemeAlgo")
		.def(py::init<Scheme &>())
		.def("powerOf2", &SchemeAlgo::powerOf2)
		.def("powerOf2Extended", &SchemeAlgo::powerOf2Extended)
		.def("power", &SchemeAlgo::power)
		.def("powerExtended", &SchemeAlgo::powerExtended)
		.def("inverse", &SchemeAlgo::inverse)
		.def("function", &SchemeAlgo::function)
		.def("functionLazy", &SchemeAlgo::functionLazy);

	// SecretKey
	py::class_<SecretKey>(m, "SecretKey")
		.def(py::init<Ring &>());

	// StringUtils
	py::class_<StringUtils>(m, "StringUtils")
		// SHOW ARRAY
		.def_static("showVec", (void (*)(long *, long)) & StringUtils::showVec)
		.def_static("showVec", (void (*)(double *, long)) & StringUtils::showVec)
		.def_static("showVec", (void (*)(complex<double> *, long)) & StringUtils::showVec)
		.def_static("showVec", (void (*)(ZZ *, long)) & StringUtils::showVec)
		// SHOW & COMPARE ARRAY
		.def_static("compare", (void (*)(double, double, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(complex<double>, complex<double>, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(double *, double *, long, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(complex<double> *, complex<double> *, long, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(double *, double, long, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(complex<double> *, complex<double>, long, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(double, double *, long, string)) & StringUtils::compare)
		.def_static("compare", (void (*)(complex<double>, complex<double> *, long, string)) & StringUtils::compare);

	// TimeUtils
	py::class_<TimeUtils>(m, "TimeUtils")
		.def(py::init<>())
		.def("start", &TimeUtils::start)
		.def("stop", &TimeUtils::stop);

	py::class_<SerializationUtils>(m, "SerializationUtils")
		.def_static("writeCiphertext", &SerializationUtils::writeCiphertext)
		.def_static("readCiphertext", &SerializationUtils::readCiphertext)
		.def_static("writeKey", &SerializationUtils::writeKey)
		.def_static("readKey", &SerializationUtils::readKey);
}
