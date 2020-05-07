package edu.harvard.cs50.notes;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;

public class NoteActivity extends AppCompatActivity {
    private EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note);

        Intent intent = getIntent(); //to pass one action from one activity to another
        editText = findViewById(R.id.note_edit_text);
        editText.setText(intent.getStringExtra("content"));
    }

    @Override
    protected void onPause() { //when u leave the activity
        super.onPause();

        Intent intent = getIntent();
        int id = intent.getIntExtra("id", 0);
        MainActivity.database.noteDao().save(editText.getText().toString(), id); //save content when u exit activity
    }
}
