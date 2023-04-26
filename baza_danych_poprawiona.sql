CREATE TABLE `paczkomat` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `adres_paczkomatu` varchar(255),
  `czy_jest_paczka` bool,
  `pczka_id` int
);

CREATE TABLE `paczka` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `odbiorca_id` int,
  `nadawca_id` int,
  `pczakomta_id` int,
  `rozmiar` int,
  `waga` int
);

CREATE TABLE `uzytkownik` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `imie_i_nazwisko` varchar(255),
  `email` varchar(255),
  `adres_uzytkownika` varchar(255)
);

ALTER TABLE `paczka` ADD FOREIGN KEY (`odbiorca_id`) REFERENCES `uzytkownik` (`id`);

ALTER TABLE `paczka` ADD FOREIGN KEY (`nadawca_id`) REFERENCES `uzytkownik` (`id`);

ALTER TABLE `paczka` ADD FOREIGN KEY (`pczakomta_id`) REFERENCES `paczkomat` (`id`);
