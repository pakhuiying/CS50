package edu.harvard.cs50.notes;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.room.Room;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

public class MainActivity extends AppCompatActivity {
    private RecyclerView recyclerView; //for list of notes, use recyclerView. rmb add recyclerview to build.gradle in implementation
    private RecyclerView.LayoutManager layoutManager;
    private NotesAdapter adapter;
    public static NotesDatabase database; //interact with database,
    // static means u can use the same instance of the database and access it everywhere

    @Override
    protected void onCreate(Bundle savedInstanceState) { //on loading page, set content
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        database = Room
                .databaseBuilder(getApplicationContext(), NotesDatabase.class, "notes")
                .allowMainThreadQueries()
                .build();

        recyclerView = findViewById(R.id.recycler_view);
        layoutManager = new LinearLayoutManager(this);
        adapter = new NotesAdapter();

        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setAdapter(adapter); //new instance of adapter we just wrote

        FloatingActionButton fab = findViewById(R.id.add_note_button);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                database.noteDao().create(); //create new note
                adapter.reload(); //reload adapter after creating a new note
            }
        });
        enableSwipeToDelete();
    }

    @Override
    protected void onResume() {
        super.onResume();

        adapter.reload();
    }


    private void enableSwipeToDelete() {
        ItemTouchHelper.SimpleCallback simpleItemTouchCallback = new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.RIGHT) {
            @Override
            public boolean onMove(RecyclerView recyclerView,
                                  RecyclerView.ViewHolder viewHolder,
                                  RecyclerView.ViewHolder target) {
                return false;
            }

            @Override
            public void onSwiped(RecyclerView.ViewHolder viewHolder, int direction) {

                int position = viewHolder.getAdapterPosition();
                adapter.deleteItem(position);
                adapter.notifyDataSetChanged();
            }


        };
        ItemTouchHelper itemTouchhelper = new ItemTouchHelper(simpleItemTouchCallback);
        itemTouchhelper.attachToRecyclerView(recyclerView);
    }
}
