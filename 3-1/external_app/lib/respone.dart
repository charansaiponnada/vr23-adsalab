import 'package:flutter/material.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(home: ResponsivePage());
  }
}

class ResponsivePage extends StatelessWidget {
  const ResponsivePage({super.key});

  @override
  Widget build(BuildContext context) {
    final width = MediaQuery.of(context).size.width;

    return Scaffold(
      appBar: AppBar(title: const Text('Responsive UI')),
      body: Center(
        child: Text(
          width < 600
              ? 'Mobile View'
              : width < 1024
              ? 'Tablet View'
              : 'Desktop View',
          style: const TextStyle(fontSize: 24),
        ),
      ),
    );
  }
}
