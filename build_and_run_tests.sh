#!/bin/bash

# Passo 1: Reconfigurar e compilar
echo "🔄 Configurando e compilando com Meson..."
meson setup builddir --reconfigure
meson compile -C builddir || exit 1

# Passo 2: Encontrar e correr todos os testes
echo "🚀 A correr todos os testes em subdiretórios de ch2_structs..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch2_structs/
find builddir/ch2_structs -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;

