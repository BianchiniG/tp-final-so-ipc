#!/usr/bin/env python

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.label import Label

class Colas(Widget):
    pass

class PruebaApp(App):
    def build(self):
        return Colas()

    contador = 0
    def agregar_otro(self):
        self.root.ids.agregable.add_widget(
            Label(text="Cliente %d" % self.contador)
        )
        self.contador += 1

    def eliminar_uno(self):
        if self.root.ids.agregable.children:
            self.root.ids.agregable.remove_widget(self.root.ids.agregable.children[0])
            if len(self.root.ids.agregable.children) == 0:
                self.contador = 0
if __name__ == '__main__':
    app = PruebaApp()
    app.run()
