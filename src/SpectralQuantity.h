#ifndef SPECTRALQUANTITY_H_
#define SPECTRALQUANTITY_H_

class SpectralQuantity {
public:
   // Faixas de comprimento de onda (r - g - b)
   //FIXME placeholder pra tentar implementar logo algo funcional
   //FIXME valores default no construtor pra facilitar instanciação de variáveis normais
   SpectralQuantity(float r = 0.0, float g = 0.0, float b = 0.0);

   SpectralQuantity operator+(const SpectralQuantity& s) const;
   SpectralQuantity operator*(const SpectralQuantity& s) const;
   SpectralQuantity operator/(const SpectralQuantity& s) const
   {
	   return SpectralQuantity(data[0]/s.data[0], data[1]/s.data[1], data[2]/s.data[2]);
   }


   double data[3]; 
};

#endif

