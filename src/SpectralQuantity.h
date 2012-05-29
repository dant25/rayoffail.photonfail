#ifndef SPECTRALQUANTITY_H_
#define SPECTRALQUANTITY_H_

class SpectralQuantity {
public:
   // Faixas de comprimento de onda (r - g - b)
   //FIXME placeholder pra tentar implementar logo algo funcional
   //FIXME valores default no construtor pra facilitar instanciação de variáveis normais
   SpectralQuantity(float r = 0.0, float g = 0.0, float b = 0.0);

   SpectralQuantity operator+(const SpectralQuantity& s) const;
   SpectralQuantity& operator+=(const SpectralQuantity& s);
   SpectralQuantity operator*(const SpectralQuantity& s) const;
   SpectralQuantity operator*=(const SpectralQuantity& s);
   SpectralQuantity operator*(float s) const;
   SpectralQuantity operator/(float) const;
   SpectralQuantity& operator/=(float);

   double data[3]; 
};

#endif

