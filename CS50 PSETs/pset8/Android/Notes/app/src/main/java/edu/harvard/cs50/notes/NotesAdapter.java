package edu.harvard.cs50.notes;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;

public class NotesAdapter extends RecyclerView.Adapter<NotesAdapter.NoteViewHolder> {
    //adapter is use to manage the data in recycler view and how data can be displayed
    public static class NoteViewHolder extends RecyclerView.ViewHolder {
        public LinearLayout containerView;
        public TextView nameTextView;

        public NoteViewHolder(View view) { //constructor
            super(view);
            this.containerView = view.findViewById(R.id.note_row);
            this.nameTextView = view.findViewById(R.id.note_row_name);

            this.containerView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Context context = v.getContext();
                    Note note = (Note) containerView.getTag();
                    Intent intent = new Intent(v.getContext(), NoteActivity.class);
                    intent.putExtra("id", note.id);
                    intent.putExtra("content", note.content);

                    context.startActivity(intent); //intent is like a segue
                }
            });
        }
    }

    private List<Note> notes = new ArrayList<>();

    @Override
    public NoteViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.note_row, parent, false);

        return new NoteViewHolder(view); //view that it's going to hold
    }

    @Override
    public void onBindViewHolder(NoteViewHolder holder, int position) {
        Note current = notes.get(position); //get position of notes.
        holder.containerView.setTag(current); //link to containerview
        holder.nameTextView.setText(current.content);
    }

    @Override
    public int getItemCount() {
        return notes.size();
    } //get number of notes/list

    public void reload() { //load everything from database
        notes = MainActivity.database.noteDao().getAll(); //database can be accessed from mainactivity becus it's static
        notifyDataSetChanged(); //tell recycler view to reload itself
    }

    public void deleteItem(int position) {
        int id = notes.get(position).id;
        MainActivity.database.noteDao().delete(id);
        notes.remove(position);
        notifyItemRemoved(position);
    }


}