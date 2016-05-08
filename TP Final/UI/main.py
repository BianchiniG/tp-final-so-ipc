#!/usr/bin/env python
#-*- coding: utf-8 -*-

from kivy.support import install_twisted_reactor
install_twisted_reactor()

import sys
import subprocess
from kivy.core.window import Window
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.factory import Factory
from leer_struct import buscar_estructura
from threading import Thread

TMensaje = buscar_estructura(
    '../TP/comm.h',
    'TMensaje'
)

from twisted.internet import protocol, reactor

class EscuchaC(protocol.Protocol):
    def __init__(self, app):
        self.app = app

    def datagramReceived(self, data, direccion):
        m = TMensaje()
        m.unpack(data)
        self.app.llego_mensaje(m)
        self.app.cant_mensajes = 0


class Ventana(Widget):
    pass


class Barbero(App):
    Window.size = (450, 340)    # Cambia el tamaño de la ventana

    procesos = {}   # Diccionario {'proceso', <pid>}
    cant_mensajes = NumericProperty(0)

    def build(self):
        reactor.listenUDP(2016, EscuchaC(self))
        return Ventana()

    def llego_mensaje(self, mensaje):
        '''
        m es del tipo TMensaje o sea que tiene
        todo lo que escibimos en c/comm.h adentro
        del struct {} TMensaje
        '''
        area_visualizacion = self.root.ids.vis
        if not m.pid in self.procesos:

            grafico = Factory.Proceso(
                # Agregar un elemento a la pantalla
                x=area_visualizacion.x + m.x,
                y=area_visualizacion.y + m.y,
                source=m.imagen.strip('\x00')
            )
            area_visualizacion.add_widget(grafico)

            self.procesos[m.pid] = grafico
        else:

            proceso = self.procesos[m.pid]
            if m.estado == -1:
                area_visualizacion.remove_widget(
                    proceso
                )
                del self.procesos[m.pid]

            proceso.x = m.x + area_visualizacion.x
            proceso.y = m.y + area_visualizacion.y
            if m.imagen:
                proceso.source = m.imagen

    def limpiar(self):
        subprocess.call(
            'cd ../TP &&'
            'make clean &&'
            'echo "Limpieza OK."',
            shell=True
        )

    def compilar(self):
        subprocess.call(
            'cd ../TP &&'
            'make all &&'
            'echo "Compilación OK."',
            shell=True
        )

    def ejecutar():
        hilo_barbero = Thread(target=subprocess.call, args='./TP/barbero')
        hilo_clientes = Thread(target=subprocess.call, args='./TP/clientes')
        hilo_barbero.start()
        hilo_clientes.start()

    def salir(self):
        sys.exit(1)

if __name__ == '__main__':
    Barbero().run()
