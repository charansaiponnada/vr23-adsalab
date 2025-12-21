// flutter pub add http
// flutter pub get

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() => runApp(MaterialApp(home: ApiDemo()));

class ApiDemo extends StatefulWidget {
  @override
  State<ApiDemo> createState() => _ApiDemoState();
}

class _ApiDemoState extends State<ApiDemo> {
  List data = [];

  @override
  void initState() {
    super.initState();
    fetchData();
  }

  fetchData() async {
    var res = await http.get(
      Uri.parse('https://jsonplaceholder.typicode.com/posts'),
    );
    setState(() => data = json.decode(res.body));
  }

  @override
  Widget build(BuildContext c) {
    return Scaffold(
      appBar: AppBar(title: Text('API Demo')),
      body: data.isEmpty
          ? Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: data.length,
              itemBuilder: (_, i) => ListTile(
                title: Text(data[i]['title']),
                subtitle: Text(data[i]['body']),
              ),
            ),
    );
  }
}
