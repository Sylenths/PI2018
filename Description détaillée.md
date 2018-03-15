Le joueur doit protéger plusieurs humains et infrastructures.

Le joueur aura à sa disposition plusieurs objets, de diverses formes, composés de matériaux différents, avec différentes caractéristiques et liable à d’autres objets.

Ces objets prennent un certain temps à construire et à réparer selon le nombre d’humains restant. Ces objets seront endommagés ou détruits par des vagues d’ennemis ainsi que des intempéries et diverses catastrophes naturelles.

Afin de se procurer des objets, il existe deux types de monnaies : l’énergie et les SIMcoins. L’énergie est gagnée selon le nombre de sources d’énergie connectées tandis que les SIMcoins sont gagnés à la fin d’un tour selon le nombre de structures de minage et de l’énergie disponible.

// TODO : Décrire les phases de jeu en précisant comment se déroule un tour.

La première phase d'un tour cera celle ou le joueur devra construire ou réparer sa base. son objectif primaire sera de protéger ses humains et il pourra aussi, à sa guise, protéger ses machines et autres infrastructures. Il disposera d'un certain nombre de SIMCoin qu'il devra utiliser pour acheter les pièces ou les appareils dont-il à besoin. Le joueur aura aussi besoin de gérer l'énergie dont-il dispose. L'orsque celui-ci utilisera des appareils, ceux-ci consommeront de l'énergie et il devra alouer un certain nombre d'énergie pour les appareils ce qui affectera leur efficacité.

La deuxième phase est celle ou une catastrophe se produit. Cette phase comportera certains type d'intempéries qui endomagerons les structures du joueurs et infligera des blessures aux humains.

// TODO : Décrire tous les types de matériaux et toutes les caractéristiques en précisant les effets sur la jouabilité.

// TODO : Décrire les « bâtiments » connus à ce jour, tels les sources d'énergie et les mineurs de SIMcoin.

Les objets connus sont séparés en deux catégories : les structures et les machines. Les structures sont utilisées pour construire l'abri, disponiples en plusieurs matériaux, tandis que les machines sont des objets utilisant les monnaies, connectés avec les fils.

Machines | Description
------------ | -------------
Héolienne | Génère de l'énergie avec la force du vent
Panneau solaire | Génère de l'énergie avec la lumière du soleil
Pile | Permet d'emagasiner l'énergie qui n'est pas utilisé à chaque tour
Fil conducteur | Permet de transporter le courant généré aux appareils/piles. Le joueur aura le choix entre 2 types de matériaux et un diamètre qui affecteron la résistance du fil
Interrupteur | S'installe en serie avec des fils conducteur et permet de couper le courant
Régulateur de température | Le joueur poura choisir une augmentation ou diminution de la température ambiante. le choix affectera la consomation d'énergie du régulateur
SIMCoin Miner | Il poura générer un certain nombre de nombre aléatoire à chaque tour qui sera déterminé par le joueur et qui affectera sa consomation d'énergie. S'il trouve le bon nombre, un SIMCoin sera généré et une autre réponse sera généré
Champ de force | Selon un certain volume qui sera déterminé par le joueur et qui affectera sa consomation d'énergie, le champ de force diminuera la vitesse des projectiles entrant

Structure | Description | Construction 
------------ | ------------- | ------------- 
Cube | Sert de fondation | Le joueur choisi la largeur et longueur et place la fondation. 
Mur | Va sur la fondation, protège des intempéries | Le joueur sélectionne la fondation, la longueur du mur et la hauteur. Il peut ne pas sélectionner de fondation mais les murs seront plus vulnérables. 
Toit | Va sur les murs | Disponibles en plusieurs types (plat, hexagonal, pyramidal), le joueur choisi la longueur, le type et la grosseur. Détruit lorsqu'il n'est soutenu que par deux ou moins murs. 
Planché | Permet de faire des étages et certains types de toits | Le joueur choisi les murs ainsi que la largeur et longueur

 Materiaux | Resistance | Masse | Points de rupture | Prix
 ------------ | ------------- | ------------ | ------------- | ------------
 Carton | 5 | 2 | 5 | 1
 Bois | 4 | 3 | 4 | 2
 Pierre | 3 | 4 | 3 | 3
 Métal | 2 | 5 | 2 | 4
 SIMtium | 1 | 1 | 1 | 5
 
La résistance du matériaux change la quantité de Newton nécessaire afin de l'emdommager. La masse affecte le poids d'une structure dans une gravité quelconque. Le point de rupture est la capcité qu'à un matériaux à soutenir un autre. Par exemple, un abri fait d'une fondation en carton et de murs en métal sera incapable de se soutenir car la masse du métal est de beaucoup supérieure à celle du carton et le point de rupture du carton est très faible. Le prix est le montant de ressources nécessaire afin de construire une structure en un certain matériaux. 

// TODO : Décrire en détail la démonstration d'une partie.

Au début de la partie le joueur sera dans un monde avec 10 humains qu'il va devoir protéger, une pile chargée avec 100 energie et un SIMCoin Miner. Il aura 100 SIMCoin qu'il poura utiliser pour acheter des structures et des machines.

Par exemple, le joueur pourrait acheter des cubes de carton pour faire les fondations de sa base qui pourrait être de grandeur 5x5 ce qui coûte 48 SIMCoins auquel il pourrait connecter des murs en carton de 2 de haut ce qui coûte 32 SIMCoins. De plus, il connecte son SIMCoin Miner à sa pile avec un fil de cuivre de 2mm de diametre d'une longueur de 3m ce qui coûte 3 SIMCoins et le fait fonctioner a pleine capacité.
Lorsque la phase de construction est terminer la premiere catastrophe se produit. Le premier intemperie est un vent léger qui endomage legerement les murs en carton.
À la fin de la vague le joueur se voit alouer 146 SIMCoins par son SIMCoin Miner qui utilise 75 énergie.

Dans le deuxième tour le joueur répare les murs en carton et achète une héolienne pour 175 SIMCoins qu'il connecte à sa pile avec un fil de cuivre de 2mm de diametre d'une longueur de 4m ce qui coûte 4 SIMCoins.
Lorsque la phase de construction est terminer la deuxième catastrophe se produit. Le deuxième intemperie est un vent très léger qui endomage legerement les murs en carton mais génère de l'énergie grace à l'héolienne. De plus la pluie endomage les structure en carton, la pile, le SIMCoin Miner et les humains perdent de la vie à cause de la pluie.
À la fin de la vague le joueur se voit alouer 138 SIMCoins par son SIMCoin Miner et 10 énergies avec l'héolienne, mais le SIMCoin Miner utilise 50 énergie.

Dans le troisième tour le joueur répare les murs en carton et ces machines. De plus, il ajoute un toit en bois à quatre plan de taille 5x5x3 se wui lui coute 100 SIMCoins qu'il place sur sa base.
Lorsque la phase de construction est terminer la deuxième catastrophe se produit. Le troisième intemperie est un tremblement de terre qui détruit les murs en carton ce qui cause la chute du toit. Ce dernier tombe sur les humains et les tue. 
Puisque tout les humains sont mort la partie est terminer.
