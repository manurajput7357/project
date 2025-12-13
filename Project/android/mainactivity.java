package com.example.todolidt;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private EditText etTask;
    private Button btnAdd;
    private ListView lvTasks;

    private ArrayList<String> taskList;
    private ArrayAdapter<String> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize views
        etTask = findViewById(R.id.etTask);
        btnAdd = findViewById(R.id.btnAdd);
        lvTasks = findViewById(R.id.lvTasks);

        // Initialize task list and adapter
        taskList = new ArrayList<>();
        adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, taskList);
        lvTasks.setAdapter(adapter);

        // Button click listener
        btnAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String task = etTask.getText().toString().trim();

                if (!task.isEmpty()) {
                    // Add task to list and notify adapter
                    taskList.add(task);
                    adapter.notifyDataSetChanged();

                    // Clear EditText
                    etTask.setText("");

                } else {
                    Toast.makeText(MainActivity.this, "Please enter a task", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
