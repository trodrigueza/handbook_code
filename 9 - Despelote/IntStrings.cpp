#include <iostream>
#include <string>
#include <algorithm>

// Compara valores absolutos: retorna 1 si |a|>|b|, -1 si |a|<|b|, 0 si iguales
int compararAbs(const std::string& a, const std::string& b) {
    if (a.size() != b.size())
        return a.size() > b.size() ? 1 : -1;
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

// Suma dos strings numéricos positivos (sin signo)
std::string sumarAbs(const std::string& a, const std::string& b) {
    std::string resultado;
    int i = a.size() - 1, j = b.size() - 1, acarreo = 0;

    while (i >= 0 || j >= 0 || acarreo) {
        int digitoA = (i >= 0) ? a[i--] - '0' : 0;
        int digitoB = (j >= 0) ? b[j--] - '0' : 0;
        int suma = digitoA + digitoB + acarreo;
        acarreo = suma / 10;
        resultado.push_back((suma % 10) + '0');
    }

    std::reverse(resultado.begin(), resultado.end());
    return resultado;
}

// Resta dos strings numéricos positivos (asume a >= b)
std::string restarAbs(const std::string& a, const std::string& b) {
    std::string resultado;
    int i = a.size() - 1, j = b.size() - 1, prestamo = 0;

    while (i >= 0) {
        int digitoA = a[i--] - '0';
        int digitoB = (j >= 0) ? b[j--] - '0' : 0;
        int resta = digitoA - digitoB - prestamo;

        if (resta < 0) {
            resta += 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }
        resultado.push_back(resta + '0');
    }

    std::reverse(resultado.begin(), resultado.end());

    // Eliminar ceros a la izquierda
    size_t inicio = resultado.find_first_not_of('0');
    if (inicio == std::string::npos) return "0";
    return resultado.substr(inicio);
}

// Elimina ceros a la izquierda y maneja "-0"
std::string limpiar(std::string s) {
    bool negativo = !s.empty() && s[0] == '-';
    std::string cuerpo = negativo ? s.substr(1) : s;

    size_t inicio = cuerpo.find_first_not_of('0');
    if (inicio == std::string::npos) return "0";
    cuerpo = cuerpo.substr(inicio);

    return negativo ? "-" + cuerpo : cuerpo;
}

// Suma dos enteros grandes (con signo) representados como strings
std::string sumarStrings(std::string a, std::string b) {
    bool negA = !a.empty() && a[0] == '-';
    bool negB = !b.empty() && b[0] == '-';
    if (negA) a = a.substr(1);
    if (negB) b = b.substr(1);

    std::string resultado;

    if (negA == negB) {
        // Mismo signo: se suman las magnitudes
        resultado = sumarAbs(a, b);
        if (negA) resultado = "-" + resultado;
    } else {
        // Signos distintos: se restan las magnitudes
        int cmp = compararAbs(a, b);
        if (cmp == 0) return "0";
        if (cmp > 0) {
            resultado = restarAbs(a, b);
            if (negA) resultado = "-" + resultado;
        } else {
            resultado = restarAbs(b, a);
            if (negB) resultado = "-" + resultado;
        }
    }

    return limpiar(resultado);
}

// Resta dos enteros grandes (con signo) representados como strings
std::string restarStrings(const std::string& a, const std::string& b) {
    // a - b es equivalente a a + (-b)
    std::string bNegado;
    if (!b.empty() && b[0] == '-')
        bNegado = b.substr(1);       // era negativo, ahora positivo
    else
        bNegado = "-" + b;           // era positivo, ahora negativo

    if (b == "0") bNegado = "0";

    return sumarStrings(a, bNegado);
}

int main() {
    std::string x = "123456789012345678901234567890";
    std::string y = "987654321098765432109876543210";

    std::cout << "Suma: " << sumarStrings(x, y) << std::endl;
    std::cout << "Resta: " << restarStrings(x, y) << std::endl;

    std::cout << "Suma con negativos: " << sumarStrings("-500", "300") << std::endl;
    std::cout << "Resta con negativos: " << restarStrings("-500", "-300") << std::endl;

    return 0;
}
