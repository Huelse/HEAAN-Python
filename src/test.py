from HEAAN import *

logq = 300
logp = 30
logn = 10
n = 1*2**logn
slots = n

ring = Ring()
secretKey = SecretKey(ring)
scheme = Scheme(secretKey, ring)
scheme.addLeftRotKeys(secretKey)

mevc1 = ComplexDouble()
mevc1 = EvaluatorUtils.randomComplexArray(slots)

mevc2 = ComplexDouble()
mvec2 = EvaluatorUtils.randomComplexArray(slots)

print('Plaintext1:')
StringUtils.showVec(mevc1, 2)

print('Plaintext2:')
StringUtils.showVec(mvec2, 2)


cipher1 = Ciphertext()
scheme.encrypt(cipher1, mevc1, n, logp, logq)
SerializationUtils.writeCiphertext(cipher1, './cipher1.bin')

cipher2 = Ciphertext()
scheme.encrypt(cipher2, mvec2, n, logp, logq)
SerializationUtils.writeCiphertext(cipher2, './cipher2.bin')

cipherAdd = Ciphertext()
scheme.add(cipherAdd, cipher1, cipher2);

cipherMult = Ciphertext()
scheme.mult(cipherMult, cipher1, cipher2)

cipherMultAfterReScale = Ciphertext()
scheme.reScaleBy(cipherMultAfterReScale, cipherMult, logp)

idx = 1
cipherRot = Ciphertext()
scheme.leftRotateFast(cipherRot, cipher1, idx)

dvec1 = ComplexDouble()
dvec2 = ComplexDouble()

dvec1 = scheme.decrypt(secretKey, cipher1)
dvec2 = scheme.decrypt(secretKey, cipher2)

print('Resultext1:')
StringUtils.showVec(dvec1, 2)

print('Resultext2:')
StringUtils.showVec(dvec2, 2)
