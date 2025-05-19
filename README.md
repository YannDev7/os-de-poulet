# BONOBOS

Notre OS implémente:

- paging
- interupts
- user mode (voir kernel.c)
- keyboard driver
- shell élémentaire (avec vga pour la couleur)
- driver son SB16 (fonctionne mal avec une version de QEMU > 2.0)

L'émulation avec QEMU fonctionne sur 3 OS (Windows, Arch et Mac OS Sequoia)

# Paging

Implémentation usuelle du paging. On notera l'astuce de la page 1023 du page directory dont l'adresse est celle du page directory lui-même. Cette astuce permet d'accéder au page directory une fois le paging activé.

# Keyboard driver

On utilise un scan code interne au noyau. Ainsi, on isole la logique spécifique au clavier de la conversion entre le scan code hardware et la sémantique de la touche pressée. Il devient donc facile de supporter divers layouts: il suffit de rajouter une map de conversion vers le scan code interne (et le reste du code de l'os est inchangé).

Remarque: caps et shift sont supportées. Aussi, tous les symboles du clavier ne sont pas implémentés.

# User mode

Dans kernel.c, jump_usermode permet de passer en usermode

# Audio

Implémentation du driver SB16 en suivant osdev wiki https://wiki.osdev.org/Sound_Blaster_16.

Nous avons converti un wav de cri de singe en PCM raw avec la commande ffmpeg puis le fichier raw en fichier .h avec xxd.

Pour que l'audio fonctionne, il faut ajouter les paramètres suivants à la commande de compilation dans qemu.sh:

-m 128 -device sb16,audiodev=snd0 -audiodev coreaudio,id=snd0,out.frequency=44100,out.channels=2

A noter que sur les version de qemu > 2.0, on entend seulement un bruit saturé et pas le cri de singe et le son ne fonctionne que sur Mac OS Sequoia (les paramètres à ajouter dans qemu.sh dépendent très fortement de la version exacte de qemu)