package fr.unice.miage;

import java.net.URL;
import java.net.URLClassLoader;

public class Main {
	static public void main(String[] args) {
		URL[] url = new URL("C:\\Users\\hugob\\Desktop\\eclipse-workspace\\TP3_Test\\src\\fr\\unice\\miage");
		URLClassLoader ucl = new URLClassLoader(url);
	}
}
