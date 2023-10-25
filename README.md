# Proiect-POO
Acesta este proiectul la Programare Orientata pe Obiecte, dezvoltat in Microsoft Visual Studio 2022.
Tema proiectului este "Gestiunea unei universitati", folosind 5 clase specifice. 
Acesta utilizeaza concepte de compunere, mostenire, fisiere binare, generare rapoarte, meniu principal, clase abstracte, librarii STL, metode virtuale si fisiere CSV.

const places = ['FROG', 'Camera din Față', 'Matei', 'Carrefour'];

// Funcția getPlacesNames va returna numele locurilor într-un mod asincron folosind un callback
const getPlacesNames = (callback) => {
  setTimeout(() => {
    callback(places);
  }, 1000); // Simulăm o întârziere de 1 secundă pentru a simula un comportament asincron
};

// Funcția getPlacesTypes va determina dacă locul este cafenea sau restaurant într-un mod asincron folosind un callback
const getPlacesTypes = (names, callback) => {
  setTimeout(() => {
    const types = names.map((name) => ({
      name,
      isCoffeeShop: name.length % 2 === 0,
    }));
    callback(types);
  }, 1500); // Simulăm o întârziere de 1.5 secunde pentru a simula un comportament asincron
};

// Funcția printPlacesInfo va afișa numele localului și dacă este cafenea sau nu
const printPlacesInfo = () => {
  getPlacesNames((names) => {
    getPlacesTypes(names, (placesWithTypes) => {
      placesWithTypes.forEach((place) => {
        console.log(`Nume: ${place.name}, Cafenea: ${place.isCoffeeShop}`);
      });
    });
  });
};

// Apelăm funcția printPlacesInfo pentru a obține și afișa informațiile despre locuri
printPlacesInfo();
