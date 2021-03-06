#!/usr/bin/env python
# coding=utf-8

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
from kivy.core.image import Image
from kivy.animation import Animation
from leer_struct import buscar_estructura
from threading import Thread
from kivy.properties import NumericProperty
from twisted.internet import protocol, reactor

TMensaje = buscar_estructura(
    './c/comm.h',
    'TMensaje'
)


class EscuchaC(protocol.Protocol):
    def __init__(self, app):
        self.app = app

    def datagramReceived(self, data, direccion):
        m = TMensaje()
        if len(data) != 360:
            pass
            # import pdb; pdb.set_trace()
        m.unpack(data)
        self.app.llego_mensaje(m)
        self.app.cant_mensajes = 0


class Ventana(Widget):
    pass


class VisualApp(App):
    count = 0
    procesos = {}
    cant_mensajes = NumericProperty(0)
    asientos = {'1' : 0,
                '2' : 0,
                '3' : 0}
    icon = './Chars/icono.png'
    title = 'Barbero Dormilon - Sistemas Operativos 2016'

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

    def compilar(self):
        subprocess.call(
            'gcc ./c/comm.c ./c/barbero.c  -lrt -o ./c/barbero &&'
            'gcc ./c/comm.c ./c/cliente.c  -lrt -o ./c/cliente &&'
            'echo "Compilacion OK"', shell=True)

    def ejecutar(self, comando):
        hilo = Thread(target=subprocess.call,
        args=(comando,))
        hilo.start()
        #subprocess.call(comando)

    def llego_mensaje(self, m):
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

            # Dibuja en pantalla sólo si el source no es nulo.  TODO ver
            if grafico.source is not '':
                area_visualizacion.add_widget(grafico)
                self.procesos[m.pid] = grafico
            else:
                del grafico
        else:
            proceso = self.procesos[m.pid]
            if m.estado == -1:
                area_visualizacion.remove_widget(proceso)
                del self.procesos[m.pid]

            proceso.x = m.x + area_visualizacion.x
            proceso.y = m.y + area_visualizacion.y
            if m.estado == 2:
                self.sentarse(m, proceso)
            if m.imagen is not None:
                proceso.source = m.imagen
            if m.estado == 3:
                self.levantarse(m)

    def sentarse(self, m, p):
        if self.asientos['1'] == 0:
            p.x -= 75
            self.asientos['1'] = m.pid
        elif self.asientos['2'] == 0:
            self.asientos['2'] = m.pid
        elif self.asientos['3'] == 0:
            p.x += 75
            self.asientos['3'] = m.pid

    def levantarse(self, m):
        for i in self.asientos.iterkeys():
            if self.asientos[i] == m.pid:
                self.asientos[i] = 0


if __name__ == '__main__':
    VisualApp().run()
