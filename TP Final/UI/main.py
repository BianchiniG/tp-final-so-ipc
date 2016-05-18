#!/usr/bin/env python

from kivy.support import install_twisted_reactor
install_twisted_reactor()

import os
import signal
import sys
import subprocess
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.factory import Factory
from leer_struct import buscar_estructura
from threading import Thread
from kivy.properties import NumericProperty

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
    procesos = {}
    cant_mensajes = NumericProperty(0)

    def build(self):
        reactor.listenUDP(2016, EscuchaC(self))
        return Ventana()

    def matar_a_todos(self):
        area_visualizacion = self.root.ids.vis
        for pid, grafico in self.procesos.iteritems():
            try:
                os.kill(pid, signal.SIGKILL)
            except:
                pass
            area_visualizacion.remove_widget(grafico)
            self.procesos = {}
        subprocess.call('rm /dev/shm/sem.*', shell=True)

    def limpiar(self):
        subprocess.call('cd ../TP &&'
                        'make clean &&'
                        'echo "Limpieza OK"',
                        shell=True)

    def compilar(self):
        subprocess.call(
            'cd ../TP/ &&'
            'make &&'
            'echo "Compilacion OK"', shell=True)

    def ejecutar(self, comando):
        hilo = Thread(target=subprocess.call,
        args=(comando,))
        hilo.start()

    def llego_mensaje(self, m):
        '''
        m es del tipo TMensaje o sea que tiene
        todo lo que escibimos en c/comm.h adentro
        del struct {} TMensaje
        '''
        area_visualizacion = self.root.ids.vista
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

    def salir(self):
        sys.exit(0)

if __name__ == '__main__':
    Barbero().run()
