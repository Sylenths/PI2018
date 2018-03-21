# But

Le joueur devra gérer des infrastructures afin de protéger des humains d'intempéries environnementales.

# Description

La première phase d'un tour cera celle où le joueur devra construire ou réparer sa base. Son objectif primaire sera de protéger ses humains et il pourra aussi, à sa guise, protéger ses machines et autres infrastructures. Il disposera d'un certain nombre de SIMCoins qu'il devra utiliser pour acheter les pièces ou les appareils dont-il à besoin. Le joueur devra gérer l'énergie dont-il dispose. Lorsque celui-ci utilisera des appareils, ceux-ci consommeront de l'énergie et il devra alouer un certain nombre d'énergie pour les appareils,  ce qui affectera leur efficacité.

La deuxième phase est celle où une catastrophe se produit. Cette phase comportera certains types d'intempéries qui endommagerons les structures du joueur et infligera des blessures aux humains.

# Objets

Le joueur aura à sa disposition plusieurs objets, de diverses formes, composés de matériaux différents, avec différentes caractéristiques et liables à d’autres objets.

Ces objets prennent un certain temps à construire et à réparer selon le nombre d’humains restant. Ces objets seront endommagés ou détruits par des intempéries et diverses catastrophes naturelles.

Afin de se procurer des objets, il existe deux types de ressources : l’énergie et les SIMCoins. L’énergie est gagnée selon le nombre de sources d’énergie connectées tandis que les SIMCoins sont gagnés à la fin d’un tour selon le nombre de structures de minage et l’énergie disponible.

Les objets connus sont séparés en deux catégories : les structures et les machines.

## Machines

Les machines sont des objets utilisant les monnaies, connectés avec les fils.

Machines | Description
------------ | -------------
Éolienne | Génère de l'énergie avec la force du vent.
Panneau solaire | Génère de l'énergie avec la lumière du soleil.
Pile | Emmagasine l'énergie qui n'est pas utilisé à chaque tour.
Fil conducteur | Transporte le courant généré aux appareils/piles. Le joueur aura le choix entre deux types de matériaux et un diamètre qui affecteron la résistance du fil.
Interrupteur | Couper le courant. S'installe en serie avec des fils conducteurs.
Régulateur de température | Modifie la température. Le joueur pourra choisir une augmentation ou diminution de la température ambiante. Le choix affectera la consommation d'énergie du régulateur.
SIMCoins Miner | Génère un certain nombre de nombres aléatoires à chaque tour qui sera déterminé par le joueur et qui affectera sa consommation d'énergie. S'il trouve le bon nombre, un SIMCoin sera ajouté au total du joueur et un nouveau nombre sera généré. Plus le joueur choisit de nombres, plus ça consommera de l'énergie. En revanche, si il est chanceux et trouve les bons nombres rapidement, il trouvera beaucoup de SIMCoins.
Champ de force | Diminue la vitesse des projectiles entrant, selon un certain volume qui sera déterminé par le joueur et qui affectera sa consomation d'énergie.

## Structures

Les structures sont utilisées pour construire l'abri, disponiples en plusieurs matériaux.

Structure | Description | Construction 
------------ | ------------- | ------------- 
Cube | Sert de fondation | Le joueur choisi la largeur et longueur et place la fondation. 
Mur | Va sur la fondation, protège des intempéries | Le joueur sélectionne la fondation, la longueur du mur et la hauteur. Il peut ne pas sélectionner de fondation mais les murs seront plus vulnérables. 
Toit | Va sur les murs | Disponibles en plusieurs types (plat, hexagonal, pyramidal), le joueur choisi la longueur, le type et la grosseur. Détruit lorsqu'il n'est soutenu que par deux ou moins murs. 
Planché | Permet de faire des étages et certains types de toits | Le joueur choisi les murs ainsi que la largeur et la longueur.

### Matériaux

Materiaux | Resistance | Masse | Points de rupture | Prix
------------ | ------------- | ------------ | ------------- | ------------
Carton | 5 | 2 | 5 | 1
Bois | 4 | 3 | 4 | 2
Pierre | 3 | 4 | 3 | 3
Métal | 2 | 5 | 2 | 4
SIMtium | 1 | 1 | 1 | 5
Cuivre* | 5 | ∅ | ∅ | 1
Or* | 1 | ∅ | ∅ | 5
 
La résistance du matériaux change la quantité de Newton nécessaire afin de l'emdommager. La masse affecte le poids d'une structure dans une gravité quelconque. Le point de rupture est la capcité qu'à un matériaux à soutenir un autre. Par exemple, un abri fait d'une fondation en carton et de murs en métal sera incapable de se soutenir car la masse du métal est de beaucoup supérieure à celle du carton et le point de rupture du carton est très faible. Le prix est le montant de ressources nécessaire afin de construire une structure en un certain matériaux. 

*Le cuivre et l'or sont spéciaux car ils ne sont applicables que pour les fils conducteurs. Non seulement le joueur choisira parmis deux matériaux, ce qui affectera leur résistance, mais il choisira aussi parmis deux grosseurs de fil (soit petit et gros), ce qui modifira la portée et le prix.

# Construction

Pour la construction de structures, le joueur disposera de plusieurs outils. Le premier étant un outil lui permetant de créer des fondations au sol. Les fondation permettent de créer une base solide pour les murs. Le joueur poura placer des carrés au sol et ceux-ci représenterons la première ébauche de la base. Ensuite, le joueur pourra construire automatiquement des murs à partir d'une fondation qu'il aura créé au préalable. Le joueur aura le choix de plusieurs matériaux (voir tableau des matériaux) et il pourra aussi choisir la hauteur des murs. Le choix des matériaux et la hauteur des murs affecterons le prix. Pour terminer sa base, le joueur devra y installer un toit. Plusieurs formes de toits seront disponible; Un toit simple (ou planché), un toit avec un seul pan, un toit avec deux pans et un toit avec quatres pans. Le joueur devra entrer les dimensions du toit (longueur, largeur, hauteur), et choisir un matériaux. À partir de ces données, un toit sera généré automatiquement et le joueur pourra le placer sur les murs. Le prix d'un toit sera déterminé par le type de matériaux utilisé et par son aire totale. Chaques coté de toit et chaque mur disposerons d'un point d'encrage. Un toit doit être obligatoirement connecté à au moins deux point d'encrage, sinon celui-ci s'écroule.

## Énergie


// TODO : Décrire comment seront connecté les structures et comment la distribution d'énergie aux différents objets sera géré.


# Intempéries

//TODO : Ajouter les types d'intempéries et une brève description

Intempéries | Description
------------ | -------------
Pluie/Acide | Les pluies ou les pluies acides, auront pour effet de réduire la résistance des matériaux.
Neige/Acide | La neige produira une accumulation sur les toits et cette accumulation produira une force sur le toit. Si la température se réchauffe, la neige fond et elle aura le même effet que la pluie sur les toit ou elle se serait accumulé.
Grèle/Météorites | Projectiles qui endomagent les structures/objets. Les météorites peuvent faire prendre des objets en feu.
Vent/Tornade | Le vent applique une force sur les structures et les tornades sont du vents avec des projectiles.
Feu | Le feu s'appliquerait à une certaine pièce de structure ou à une machine, et il se propagerait plus ou moins rapidement et il ferait plus ou moins de dommages dépendament du matériau.
Température | Elle affecterait le fonctionnement de certains appareils et la résistance de certains matériaux. La température infligerait aussi des dommages aux humains ne se trouvant pas dans une zone tempérée.
Éclair | Fait prendre l'objet touché en feu. Si un humain est touché, il subi des dommages.
Tremblement de terre | Réduit le point de rupture des matériaux.
Radiation | Inflige des dégats par tour aux humains se trouvant dans la zone de radiation.


# Exemple

Une partie typique se déroulerait comme suit :

*Le joueur commence la partie en phase construction dans un monde avec dix humains qu'il doit protéger, une pile chargée avec 100 énergie, 100 SIMCoins et un SIMCoins Miner.*

*Le joueur décide d'acheter des cubes en carton afin de faire une fondation de format 5 x 5 avec l'argent disponible au début de la partie. Ensuite, il y connecte des murs en carton de deux "cubes" (ont parle ici des cubes dont est fait l'environnement 3D du jeu). Il relie ensuite sa pile à son SIMCoins Miner avec du fil de cuivre de petit diamètre et fait fonctionner ce dernier à pleine capacité. Étant donné que le joueur sait que l'intempérie qu'il devra survivre est un vent faible, il décide de ne pas construire de toit et termine son tour.*

*Lorsque la phase de construction est terminé, la première péripétie se produit. C'est un vent léger qui endommage légèrement les murs en carton sans les détruire.*

*À la fin de la vague le joueur se voit alouer des SIMCoins par son SIMCoins Miner.*

*Au deuxième tour le joueur répare les murs en carton avec ses humains. Il décide d'acheter une héolienne car il sait que la prochaine intempérie sera un vent très faible. Il la connecte à sa pile et au SIMCoins avec un petit fil de cuivre. Il met en marche son héolienne et met en encore un fois son SIMCoins Miner à pleine capacité et termine son tour.*

*La deuxième péripétie est un vent très léger avec une légère pluie. Le vent et la pluie endommagent légèrement le carton, le SIMCoins Miner et la pile mais le vent a permis à l'héolienne de générer de l'énergie. Par contre, les humains ont perdu de la vie à cause de la pluie puisqu'il n'y avait pas de toit.*

*À la fin de la vague le joueur se voit aloué des SIMCoins par son SIMcoins Miner et l'énergie générée par l'héolienne a remplie la pile.*

*Au le troisième tour le joueur répare les murs en carton et ses machines avec ses humains. De plus, il ajoute un toit en bois à quatre plans de format 5 x 5 x 3 et le place sur sa base. Il ajuste le SIMCoins Miner pour qu'il n'utilise qu'une quantité moyenne d'énergie et désactive l'héolienne pour ne pas l'endommager puisque la prochaine intempérie est un tremblement de terre. Il termine son tour.*

*La troisième intempérie est un tremblement de terre qui détruit les murs en carton, ce qui cause la chute du toit. Ce dernier tombe sur les humains et les tue.*

*Puisque tous les humains sont morts la partie est terminée et le score final est compatibilisé.*

////////////////////////////

Au début de la partie, le joueur sera dans un monde avec 10 humains qu'il va devoir protéger, une pile chargée avec 100 d'énergie et un SIMCoins Miner. Il aura 100 SIMCoins qu'il poura utiliser pour acheter des structures et des machines.

Par exemple, le joueur pourrait acheter des cubes de carton pour faire les fondations de sa base qui pourrait être de grandeur 5x5 ce qui coûte 48 SIMCoins auquel il pourrait connecter des murs en carton de 2 de haut ce qui coûte 32 SIMCoins. De plus, il connecte son SIMCoin Miner à sa pile avec un fil de cuivre de 2mm de diamètre d'une longueur de 3m ce qui coûte 3 SIMCoins et le fait fonctioner a pleine capacité.
Lorsque la phase de construction est terminée, la première catastrophe se produit. Le premier intempérie est un vent léger qui endommage légèrement les murs en carton.
Vers la fin de la vague, le joueur se voit alouer 146 SIMCoins par son SIMCoin Miner qui utilise 75 énergie.

Durant le deuxième tour, le joueur répare les murs en carton et achète une héolienne pour 175 SIMCoins qu'il connecte à sa pile avec un fil de cuivre de 2mm de diamètre d'une longueur de 4m ce qui coûte 4 SIMCoins.
Lorsque la phase de construction est terminée, la deuxième catastrophe se produit. Le deuxième intemperie est un vent très léger qui endommage légèrement les murs en carton, mais génère de l'énergie grâce à l'éolienne. De plus, la pluie endommage les structures en carton, la pile, le SIMCoin Miner et les humains perdent de la vie à cause de la pluie.
Vers la fin de la vague, le joueur se voit alouer 138 SIMCoins par son SIMCoin Miner et 10 énergies avec l'éolienne, mais le SIMCoin Miner utilise 50 énergie.

Durant le troisième tour, le joueur répare les murs en carton et ces machines. De plus, il ajoute un toit en bois à quatre plan de taille 5x5x3 se wui lui coute 100 SIMCoins qu'il place sur sa base.
Lorsque la phase de construction est terminée, la deuxième catastrophe se produit. Le troisième intempérie est un tremblement de terre qui détruit les murs en carton, ce qui cause la chute du toit. Ce dernier tombe sur les humains et les tue. 
Puisque tout les humains sont mort, la partie est terminée.
