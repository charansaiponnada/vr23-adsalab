import 'package:flutter/material.dart';

void main() => runApp(
  MaterialApp(
    initialRoute: '/',
    routes: {'/': (_) => Screen1(), '/screen2': (_) => Screen2()},
  ),
);

class Screen1 extends StatelessWidget {
  @override
  Widget build(BuildContext c) => Scaffold(
    appBar: AppBar(title: Text("Screen 1")),
    body: Center(
      child: ElevatedButton(
        onPressed: () => Navigator.pushNamed(c, '/screen2'),
        child: Text("Go to Screen 2"),
      ),
    ),
  );
}

class Screen2 extends StatelessWidget {
  @override
  Widget build(BuildContext c) => Scaffold(
    appBar: AppBar(title: Text("Screen 2")),
    body: Center(
      child: ElevatedButton(
        onPressed: () => Navigator.pop(c),
        child: Text("Back"),
      ),
    ),
  );
}
