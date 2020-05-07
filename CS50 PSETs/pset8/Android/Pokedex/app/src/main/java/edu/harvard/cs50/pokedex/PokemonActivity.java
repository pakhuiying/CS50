package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView catchPokemon;
    private ImageView pokemonSprite;
    private TextView pokemonDescription;
    private String url;
    private RequestQueue requestQueue;
    //private HashMap<String, Boolean> pokemonDictionary; //= new HashMap<String, Boolean>();
    private Set pokemonDictionary;
    private Boolean isCaught;
    private SharedPreferences sharedPreferences;
    private String name;


    //private Boolean isClicked = true;
    public void toggleCatch(View view) {
        //sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        //sharedPreferences = getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        //SharedPreferences.Editor editor = sharedPreferences.edit();
        //String name = nameTextView.getText().toString().toLowerCase();
        //getPreferences(Context.MODE_PRIVATE).edit().putString("course", "Release").commit();
        //String course = getPreferences(Context.MODE_PRIVATE).getString("course", "cs50");

        String name = nameTextView.getText().toString().toLowerCase();

        //pokemonDictionary = sharedPreferences.getStringSet("Catch", new HashSet<String>());

        System.out.println(name + catchPokemon.getText().toString());

        if (catchPokemon.getText().toString().equals("Release")) {
            catchPokemon.setText("Catch");
            pokemonDictionary.remove(name);
        }

        else {
            catchPokemon.setText("Release");
            pokemonDictionary.add(name);
        }

        /*if (isCaught == true) {
            isCaught = false;
            catchPokemon.setText("Catch");
            pokemonDictionary.remove(name);
        }

        else {
            isCaught = true;
            catchPokemon.setText("Release");
            pokemonDictionary.add(name);
        }*/

        //isCaught = !isCaught;
        editor.clear();

        editor.putStringSet("Caught", pokemonDictionary);
        //String: The name of the preference to modify.
        //Set: The set of new values for the preference. Passing null for this argument is equivalent to calling remove
        editor.apply();
        /*isCaught = getPreferences(Context.MODE_PRIVATE).getBoolean(name, false);

        if (isCaught == true) {
            catchPokemon.setText("Catch");
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, false).commit();
        }

        else {
            catchPokemon.setText("Release");
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, true).commit();
        }*/

        /*if (pokemonDictionary.get(name) == null || pokemonDictionary.get(name) == false) {
            catchPokemon.setText("Release");
            pokemonDictionary.put(name, true);
            sharedPreferences.edit().putBoolean(name, true).apply();
            //getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, true).commit();
            //getPreferences(Context.MODE_PRIVATE).edit().putString(name, "Release").commit();


        }

        else {
            catchPokemon.setText("Catch");
            pokemonDictionary.put(name, false);
            sharedPreferences.edit().putBoolean(name, false).apply();
            //getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, false).commit();
            //getPreferences(Context.MODE_PRIVATE).edit().putString(name, "Catch").commit();
        }*/

        //System.out.println(pokemonDictionary.entrySet());

    }

    public void loadButtons(String name){
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        //sharedPreferences = getPreferences(Context.MODE_PRIVATE);
        //String name = nameTextView.getText().toString().toLowerCase();
        //name = (String) nameTextView.getText();
        //isCaught = false; //init is Caught
        //Boolean isCaught = sharedPreferences.getBoolean(name, pokemonDictionary.get(name));
        //catchPokemon.setText("");
        //sharedPreferences = getPreferences(Context.MODE_PRIVATE);
        //SharedPreferences.Editor editor = sharedPreferences.edit();

        if (sharedPreferences.contains("Caught")) {
            //Checks whether the preferences contains a preference.
            //pokemonDictionary = sharedPreferences.getStringSet("Caught", null);
            pokemonDictionary = sharedPreferences.getStringSet("Caught", new HashSet());
            //load pokemonDictionary
            System.out.println(pokemonDictionary);
            //getStringSet: Retrieve a set of String values from the preferences.
            //String: The name of the preference to retrieve.
            //Set: Values to return if this preference does not exist. This value may be null.
            if (pokemonDictionary.contains(name)) {
                catchPokemon.setText("Release");
                //isCaught = true;
                //catchPokemon.setText("");

            }

            else {
                //isCaught = false;
                //catchPokemon.setText("");
                catchPokemon.setText("Catch");
                //pokemonDictionary = new HashSet<>();
            }
        }

        else {
            //isCaught = false;
            catchPokemon.setText("Catch");
        }

        System.out.println("OnCreate Name: " + name);
        System.out.println("OnCreate: " + name + catchPokemon.getText().toString());
       /* if (isCaught == true) {
            catchPokemon.setText("Release");
        }

        else {
            catchPokemon.setText("Catch");
        }*/
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) { //viewdidload
        //sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        //sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        //sharedPreferences = this.getSharedPreferences(getString(R.string.preference_key), Context.MODE_PRIVATE);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        catchPokemon = findViewById(R.id.catchPokemon);
        pokemonSprite = findViewById(R.id.pokemonSprite);
        pokemonDescription = findViewById(R.id.pokemonDescription);

        load();
        loadSprite();
        loadDescription();
        //loadButtons();

        //String name = nameTextView.getText().toString().toLowerCase();
        //System.out.println("OnCreate Name: " + name);

        /*else {
            pokemonDictionary = sharedPreferences.getStringSet("Caught", new HashSet<String>());
            catchPokemon.setText("Catch");
        }*/
        //catchPokemon.setText();
        //System.out.println(pokemonDictionary.entrySet());



        //Boolean isCaught = getPreferences(Context.MODE_PRIVATE).getBoolean(name, pokemonDictionary.get(name));
        /*if (pokemonDictionary.get(name) == null) {
            catchPokemon.setText("Catch");
        }

        else if (pokemonDictionary.get(name) == true) {
            catchPokemon.setText(getPreferences(Context.MODE_PRIVATE).getString(name, "Release"));
        }

        else {
            catchPokemon.setText(getPreferences(Context.MODE_PRIVATE).getString(name, "Catch"));
        }*/






    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));

                    String name = nameTextView.getText().toString().toLowerCase();
                    System.out.println("load: " + name + "pokemonDict: " + pokemonDictionary);
                    loadButtons(name);

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> { //String is url, Bitmap is the object returned
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                //URL url = new URL(url);
                return BitmapFactory.decodeStream(url.openStream());
            } catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            pokemonSprite.setImageBitmap(bitmap);
        }
    }

    public void loadSprite(){
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    // you need to get the url!
                    //nameTextView.setText(response.getString("name"));
                    JSONObject spriteEntries = response.getJSONObject("sprites"); //JSON object, not array
                    String front_default = spriteEntries.getString("front_default"); //url to sprite image
                    new DownloadSpriteTask().execute(front_default);


                }

                catch (JSONException e) {
                    Log.e("cs50", "Pokemon sprite json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon sprite error", error);
            }
        });

        requestQueue.add(request);
    }


    public void loadDescription() {
        //pokemonDescription.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    JSONObject speciesEntries = response.getJSONObject("species"); //JSON object, not array
                    String species_url = speciesEntries.getString("url"); //url to species url

                    String name = speciesEntries.getString("name");


                    JsonObjectRequest request1 = new JsonObjectRequest(Request.Method.GET, species_url, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                JSONArray textEntries = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < textEntries.length(); i++) {
                                    JSONObject textEntry = textEntries.getJSONObject(i);
                                    String description = textEntry.getString("flavor_text");
                                    String language = textEntry.getJSONObject("language").getString("name");

                                    if (language.equals("en")) { //use equals for comparing string, not ==
                                        language = language.replace("\n"," ");
                                        pokemonDescription.setText(description);
                                        //System.out.println(description);
                                        break;
                                        //so i only select the first english description
                                    }
                                    //
                                }

                            }

                            catch (JSONException e) {
                                Log.e("cs50", "Pokemon flavour text error", e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "Pokemon flavour text details error", error);
                        }
                    });
                    requestQueue.add(request1);


                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);


    }









}
