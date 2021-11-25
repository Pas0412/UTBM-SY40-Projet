# UTBM-SY40-Projet

Ce  projet s’inspire librement du fonctionnement de  la  plate-forme  multimodale et logistique Delta3, terminal de transport combiné (rail, route et voie d’eau).

Delta 3 多式联运 介绍：http://www.delta-3.com/

Cette installation propose des services de regroupement de marchandises dans un même véhicule pour une même destination.
La combinaison des modes de transport s’articule autour :
-    Du transport ferroviaire composé d’une voie ferrée unique unidirectionnelle ;
-    Du transport maritime sur la base d’une voie d’eau bidirectionnelle ;
-    Du transport routier sur lequel circule des camions de transport ;
-    De portiques permettant de manipuler des conteneurs.

交通方式的组合围绕：
- 由一条单向铁路线组成的铁路运输；
- 以双向水路为基础的海上运输；
- 运输卡车在其上流通的公路运输；
- 用于搬运集装箱的龙门起重机。


La gestion de l’ensemble des aiguillages de la plate-forme est assurée à partir d’un système informatique centralisé .

Règles de fonctionnement (Figure A) :
-    Un train est composé d’un nombre limité de wagons. Seul deux trains sont autorisés à opérer simultanément sur la voie.
-    Seules deux péniches peuvent être amarrées en même temps.
-    Un nombre limité de camions stationnent sur la voie routière.
-    Les  containers  sont  déchargés  au  fur  et  à  mesure  des  opportunités  de stockage.
-    Le portique ne peut transporter qu’un seul container à la fois.
-    Le portique opère sur toute les voies.
-    Lors des opérations de chargement et déchargement, les portiques ne peuvent se croiser ni se télescoper.
-    La rotation des véhicules est essentielle dans la gestion logistique au même titre que la position des portiques.



操作规则（图A）：
- 火车由有限数量的车厢组成。只有两列火车允许在轨道上同时运行。
- 只能同时停泊两艘驳船。
- 数量有限的卡车停在路上。
- 随着存储机会的增加，集装箱被卸载。
- 龙门架一次只能携带一个集装箱。
- 龙门架可在所有轨道上运行。
- 在装载和卸载操作期间，龙门架不能相交或重叠（？）。
- 车辆的轮换在物流管理中至关重要，就像龙门架的位置一样。



Cette transposition se voudra cohérente et le déroulé de sa mise en oeuvre respectera la logique suivante :
-    Modélisation du système par réseau de Pétri ou formalisation simplifiée du problème   (identification   des   acteurs,   des   échanges,   identification   des ressources critiques).
-    Transposition  de  ces  formalismes  à  l’aide  des  procédés  et  moyens  de communications présentés en cours (Approche  Processus/Thread,  Files de messages, etc.).
-    Implémentation effective, debug & tests.
Conseils d’implémentation :
-    Pensez Programme modulaire ;
-    Si vous n’utilisez pas de Sémaphores ou de Moniteurs, c’est que vous passez à côté du problème.
-    Attention aux objets résiduels (Posix & IPC).
-    Attention à l’indentation du code pour permettre une meilleure lisibilité .
-    Attention aux fuites mémoires et utilisation des pointeurs.
-    Favoriser le caractère dynamique de l’application (avec paramétrage pour le lancement).
-    Utilisation  de  librairies  et  de  plusieurs  fichiers  sources  conseillés  avec  un
makefile.
-    Si implémentation sur un autre OS ou système, prévoyez des temps de portage liés aux différents comportements qui peuvent changer.



这种转换将是一致的，其实施过程将遵循以下逻辑：
- 对培养皿网络系统进行建模或简化问题的形式化（识别参与者，交换，识别关键资源）。
- 使用类中呈现的进程和通信方式（进程/线程方法，消息文件等）来转置这些形式主义。
- 有效的实施，调试和测试。
实施技巧：
- 思考模块化程序;
- 如果不使用信号量或监视器，则缺少重点。
- 当心残留物（Posix和IPC）。
- 注意代码的缩进，以允许更好的可读性。
- 谨防内存泄漏和指针的使用。
- 促进应用程序的动态性质（设置启动）。
- 使用库和几个推荐的源文件与生成文件。
- 如果在其他操作系统或系统上实现，请规划与可能更改的不同行为相关的移植时间。

