Der Code ist einsichtbar unter:
https://github.com/ahujaankush/botball-tgm-2223/

Der Code der hier dokumentiert wird, steuert 2 Roboter einen Create Roboter und einen Wallaby. Create Roboter sind umgebaute Staubsauger Roboter, die über Serial steuerbar sind. Wallaby ist der Controller der von der KIPR bereitgestellt wird, dieser steuert auch den Create, da er kein Onboard Logik hat, würde aber das bezeichnen der Roboter schwieriger machen.

Er wurde geschrieben um die Strecke beim Botball Event zu bestreiten. Dabei sollte der Create die roten Röhren aus den Türmen ziehen und der Wallaby eine Würfel verschieben um einen Schalter umzulegen, nichts davon hat funktioniert. Die Probleme lagen hauptsächlich darin, dass wir zu wenig getestet hatten.

main.c gibt bei beiden die Route an, dabei wird der Linefollower mit einem Struct gelöst und die Route über eine Funktion.

Projektstruktur:

├───botball-tgm-2223
│   ├───libwallaby
│   ├───_create
│   │   ├───arm
│   │   └───linefollower
│   └───_wombat
│       ├───arm
│      └───linefollower

_ create ist  für den create Roboter, _ wombat ist für den wombat Roboter. arm ist für die Konstanten und Methoden um die Arme zu steuern und linefollower ist eine Roboter spezifische Implementierung von einem Linefollower. Der libwallaby Folder ist da um die offiziele Libwallaby Library anzubinden. 

Das finale Produkt kann man sehen unter https://youtu.be/xAATFjmRroY.

Aus diesem Projekt kann man die Schlussfolgerungen ziehen, dass es keinen Sinn macht zu versuchen das Große Endprodukt zu machen, wenn man es noch nicht hingekriegt hat die Grundsteine zu legen.
