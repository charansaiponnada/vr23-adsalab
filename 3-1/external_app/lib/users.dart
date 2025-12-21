// flutter pub add http
// flutter pub get

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() => runApp(MaterialApp(home: UserList()));

class UserList extends StatefulWidget {
  @override
  State<UserList> createState() => _UserListState();
}

class _UserListState extends State<UserList> {
  List data = [];

  @override
  void initState() {
    super.initState();
    http
        .get(Uri.parse('https://jsonplaceholder.typicode.com/users'))
        .then((res) => setState(() => data = json.decode(res.body)));
  }

  @override
  Widget build(BuildContext c) => Scaffold(
    appBar: AppBar(title: Text('User List')),
    body: data.isEmpty
        ? Center(child: CircularProgressIndicator())
        : ListView.builder(
            itemCount: data.length,
            itemBuilder: (_, i) => Card(
              margin: EdgeInsets.all(8),
              child: ListTile(
                leading: CircleAvatar(child: Text('${data[i]['id']}')),
                title: Text(data[i]['name']),
                subtitle: Text(data[i]['email']),
              ),
            ),
          ),
  );
}
