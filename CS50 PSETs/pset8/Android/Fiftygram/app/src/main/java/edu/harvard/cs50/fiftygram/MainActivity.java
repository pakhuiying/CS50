package edu.harvard.cs50.fiftygram;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.Transformation;
import com.bumptech.glide.request.RequestOptions;

import java.io.FileDescriptor;
import java.io.IOException;

import jp.wasabeef.glide.transformations.gpu.PixelationFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SepiaFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SketchFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.ToonFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.VignetteFilterTransformation;

public class MainActivity extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback{
    private ImageView imageView;
    private Bitmap original; //use to load images
    private Button button_save;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.image_view);
        button_save = findViewById(R.id.button_save);

    }

    @Override //allow permission
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public void apply(Transformation<Bitmap> filter) {
        if (original != null) {
            Glide
                    .with(this)
                    .load(original)
                    .apply(RequestOptions.bitmapTransform(filter))
                    .into(imageView);
        }
    }

    public void applySepia(View view) {
        apply(new SepiaFilterTransformation());
    }

    public void applyToon(View view) {
        apply(new ToonFilterTransformation());
    }

    public void applySketch(View view) {
        apply(new SketchFilterTransformation());
    }

    public void applyPixelation(View view) {
        apply(new PixelationFilterTransformation());
    }

    public void applyVignette(View view) {
        apply(new VignetteFilterTransformation());
    }

    public void choosePhoto(View view) {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("image/*");
        startActivityForResult(intent, 1); //request code is a unique identifier to let system know which intent it came from
    }

    public void savePhoto(View v) {
        //Intent intent = new Intent(Intent.ACTION_MEDIA_MOUNTED);
        //intent.setType("image/*");
    //insertImage(ContentResolver cr, String imagePath, String name, String description)

        Bitmap image = ((BitmapDrawable) imageView.getDrawable()).getBitmap(); //get bitmap from image view
        //Bitmap bitmap = image.getBitmap();
        MediaStore.Images.Media.insertImage(getContentResolver(), image, "image", "image");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        //called by system when exit out of activity. after selecting photo, this method is called
        //request code will be 1, result code = other activity to specify if there's error
        //intent to pass any function back to main
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == Activity.RESULT_OK && data != null) {
            try {
                Uri uri = data.getData(); //uri smth like url, specify location of smth. gets path of data. like a pointer
                ParcelFileDescriptor parcelFileDescriptor =
                        getContentResolver().openFileDescriptor(uri, "r"); //r = read
                FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
                original = BitmapFactory.decodeFileDescriptor(fileDescriptor); //bitmapfactory = class to instantiated obj
                parcelFileDescriptor.close();
                imageView.setImageBitmap(original);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
